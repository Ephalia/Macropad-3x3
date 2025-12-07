/*
 * Arduino Pro Micro 3x3 HID Macropad
 * 
 * ATmega32U4 tabanlı özel macropad firmware'i
 * USB HID klavye ve medya kontrol cihazı olarak çalışır
 * 
 * Donanım: Arduino Pro Micro
 * Gerekli Kütüphane: HID-Project (Library Manager'dan yükleyiniz)
 * 
 * Tuş Konfigürasyonu:
 * Satır 1: Ses Azalt | Ses Arttır | Sesi Kapat
 * Satır 2: Önceki | Play/Pause | Sonraki
 * Satır 3: Alt+F4 | Win+D | Win+L
 */

#include "HID-Project.h"

// ===== PIN KONFIGÜRASYONU =====
// Arduino Pro Micro düğmelerinin GPIO pin atamalarını tanımlayın
const int BUTTON_PINS[3][3] = {
  { 4,  6, 10 },  // Satır 1: D4 (A6), D6 (A7), D10
  { 16, 14, 15 }, // Satır 2: D16 (A2), D14 (A0), D15 (A1)
  { 9, 5, 3 }     // Satır 3: D9, D5, D3
};

// Makro tipi tanımı
enum MacroType {
  MACRO_KEYBOARD,    // Klavye tuş kombinasyonu
  MACRO_CONSUMER     // Medya/Tüketici kontrol tuşu
};

// Tuş kombinasyon tanımları
struct MacroKey {
  MacroType type;      // Makro tipi (klavye veya medya)
  int modifier;        // Modifier tuşlar (sadece MACRO_KEYBOARD için)
  int key1;            // Ana tuş veya medya tuşu
  int key2;            // İkinci tuş (opsiyonel)
  int key3;            // Üçüncü tuş (opsiyonel)
};

const MacroKey MACRO_BINDINGS[3][3] = {
  // Satır 1: Ses Kontrolleri
  { { MACRO_CONSUMER, 0, MEDIA_VOLUME_DOWN, 0, 0 },   // Ses Azalt
    { MACRO_CONSUMER, 0, MEDIA_VOLUME_UP, 0, 0 },     // Ses Arttır
    { MACRO_CONSUMER, 0, MEDIA_VOLUME_MUTE, 0, 0 } }, // Sesi Kapat
  // Satır 2: Medya Kontrolleri
  { { MACRO_CONSUMER, 0, MEDIA_PREVIOUS, 0, 0 },      // Önceki
    { MACRO_CONSUMER, 0, MEDIA_PLAY_PAUSE, 0, 0 },    // Play/Pause
    { MACRO_CONSUMER, 0, MEDIA_NEXT, 0, 0 } },        // Sonraki
  // Satır 3: Sistem Komutları
  { { MACRO_KEYBOARD, KEY_LEFT_ALT, KEY_F4, 0, 0 },   // Alt+F4 (Uygulamayı Kapat)
    { MACRO_KEYBOARD, KEY_LEFT_GUI, 'd', 0, 0 },      // Win+D (Masaüstüne Git)
    { MACRO_KEYBOARD, KEY_LEFT_GUI, 'l', 0, 0 } }     // Win+L (Bilgisayarı Kilitle)
};

// ===== DEBOUNCING KONFİGÜRASYONU =====
const unsigned long DEBOUNCE_TIME = 15;  // ms cinsinden debounce süresi (15ms)
const unsigned long SCAN_INTERVAL = 1;   // ms cinsinden tarama aralığı

// Tuş durumları (debouncing için gerekli)
struct ButtonState {
  int lastState;           // Son çıkış durumu
  int currentState;        // Şu anki çıkış durumu
  unsigned long lastTime;  // Son durum değişikliğinin zamanı
  bool pressed;            // Basılı mı?
};

ButtonState buttons[3][3];

// ===== SETUP FÖNKSİYONU =====
void setup() {
  // Seri haberleşeme başlat (isteğe bağlı, hata ayıklama için)
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("Arduino Pro Micro 3x3 Macropad başlatılıyor...");
  
  // Tüm pin'leri INPUT olarak ayarla (dahili pull-up ile)
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      pinMode(BUTTON_PINS[row][col], INPUT_PULLUP);
      buttons[row][col].lastState = HIGH;
      buttons[row][col].currentState = HIGH;
      buttons[row][col].pressed = false;
      buttons[row][col].lastTime = 0;
    }
  }
  
  // USB HID cihazlarını başlat
  Keyboard.begin();
  Consumer.begin();
  
  Serial.println("Macropad başarıyla başlatıldı!");
  Serial.println("Tuş Yapılandırması:");
  Serial.println("Satır 1: Ses Azalt | Ses Arttır | Sesi Kapat");
  Serial.println("Satır 2: Önceki | Play/Pause | Sonraki");
  Serial.println("Satır 3: Alt+F4 | Win+D | Win+L");
}

// ===== ANA DÖNGÜ =====
void loop() {
  static unsigned long lastScan = 0;
  unsigned long now = millis();
  
  // Tarama aralığını kontrol et (1ms döngü)
  if (now - lastScan >= SCAN_INTERVAL) {
    lastScan = now;
    
    // Tüm düğmeleri tara ve debounce işlemini yap
    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        updateButtonState(row, col, now);
      }
    }
  }
}

// ===== DÜĞME DURUMU GÜNCELLEME FONKSİYONU (DEBOUNCING İLE) =====
void updateButtonState(int row, int col, unsigned long now) {
  ButtonState& btn = buttons[row][col];
  int pin = BUTTON_PINS[row][col];
  
  // Pin durumunu oku (LOW = basılı, HIGH = bırakılmış)
  int reading = digitalRead(pin);
  
  // Durum değişikliği algılandı
  if (reading != btn.lastState) {
    btn.lastTime = now;
    btn.lastState = reading;
  }
  
  // Yeterli süre geçti ve durum kararlı
  if ((now - btn.lastTime) >= DEBOUNCE_TIME) {
    if (reading != btn.currentState) {
      btn.currentState = reading;
      
      // Düğme basıldı (LOW -> HIGH geçişi)
      if (btn.currentState == LOW && !btn.pressed) {
        btn.pressed = true;
        executeKeyStroke(row, col);
      }
      // Düğme bırakıldı (HIGH -> LOW geçişi)
      else if (btn.currentState == HIGH && btn.pressed) {
        btn.pressed = false;
        // Tuşu bırakma (opsiyonel, bazı tuş kombinasyonları otomatik bırakılır)
      }
    }
  }
}

// ===== MAKRO TUŞU ÇALIŞTIRIR =====
void executeKeyStroke(int row, int col) {
  MacroKey macro = MACRO_BINDINGS[row][col];
  
  if (macro.type == MACRO_KEYBOARD) {
    // Klavye tuş kombinasyonu
    // Modifier tuşları işle
    if (macro.modifier & KEY_LEFT_CTRL) Keyboard.press(KEY_LEFT_CTRL);
    if (macro.modifier & KEY_LEFT_SHIFT) Keyboard.press(KEY_LEFT_SHIFT);
    if (macro.modifier & KEY_LEFT_ALT) Keyboard.press(KEY_LEFT_ALT);
    if (macro.modifier & KEY_LEFT_GUI) Keyboard.press(KEY_LEFT_GUI);
    
    // Ana tuşları işle
    if (macro.key1) Keyboard.press(macro.key1);
    if (macro.key2) Keyboard.press(macro.key2);
    if (macro.key3) Keyboard.press(macro.key3);
    
    // Tüm tuşları aynı anda bırak
    delay(50); // Kısa gecikme - tuş kombinasyonunun algılanması için
    Keyboard.releaseAll();
  } 
  else if (macro.type == MACRO_CONSUMER) {
    // Medya/Tüketici kontrol tuşu
    Consumer.write(macro.key1);
  }
  
  // Hata ayıklama çıktısı
  Serial.print("Tuş tetiklendi: Satır ");
  Serial.print(row + 1);
  Serial.print(", Sütun ");
  Serial.println(col + 1);
}
