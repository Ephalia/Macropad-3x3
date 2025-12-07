/*
 * Arduino Pro Micro 3x3 HID Macropad
 * 
 * ATmega32U4 tabanlı özel macropad firmware'i
 * USB HID klavye cihazı olarak çalışır
 * 
 * Donanım: Arduino Pro Micro
 * Kullanılan kütüphane: HID (yerleşik)
 */

#include "Keyboard.h"

// ===== PIN KONFIGÜRASYONU =====
// Arduino Pro Micro düğmelerinin GPIO pin atamalarını tanımlayın
const int BUTTON_PINS[3][3] = {
  { 4,  6, 10 },  // Satır 1: A6 (D4), A7 (D6), D10
  { 16, 14, 15 }, // Satır 2: A2 (D16), A0 (D14), A1 (D15)
  { 9, 5, 3 }     // Satır 3: D9, D5, D3
};

// Tuş kombinasyon tanımları
// Struktur: { modifier, key1, key2, key3 }
// modifier: Ctrl, Shift, Alt, GUI bitwise kombinasyonu veya 0 (yok)
struct MacroKey {
  int modifier;
  int key1;
  int key2;
  int key3;
};

const MacroKey MACRO_BINDINGS[3][3] = {
  // Satır 1
  { { KEY_LEFT_CTRL, 'c', 0, 0 },          // Ctrl+C
    { KEY_LEFT_CTRL, 'v', 0, 0 },          // Ctrl+V
    { KEY_LEFT_CTRL, 'x', 0, 0 } },        // Ctrl+X
  // Satır 2
  { { KEY_LEFT_ALT, KEY_TAB, 0, 0 },       // Alt+Tab
    { KEY_LEFT_GUI, 'd', 0, 0 },           // Win+D
    { KEY_LEFT_GUI, 'l', 0, 0 } },         // Win+L
  // Satır 3
  { { KEY_LEFT_CTRL | KEY_LEFT_ALT, 't', 0, 0 }, // Ctrl+Alt+T
    { KEY_LEFT_CTRL | KEY_LEFT_SHIFT, 'n', 0, 0 }, // Ctrl+Shift+N
    { KEY_LEFT_CTRL, 'z', 0, 0 } }         // Ctrl+Z
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
  // Seri haberleşeme başlatıl (isteğe bağlı, hata ayıklama için)
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
  
  // USB HID cihazını başlat
  Keyboard.begin();
  
  Serial.println("Macropad başarıyla başlatıldı!");
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
  
  // Modifiyer tuşları işle
  if (macro.modifier & KEY_LEFT_CTRL) Keyboard.press(KEY_LEFT_CTRL);
  if (macro.modifier & KEY_LEFT_SHIFT) Keyboard.press(KEY_LEFT_SHIFT);
  if (macro.modifier & KEY_LEFT_ALT) Keyboard.press(KEY_LEFT_ALT);
  if (macro.modifier & KEY_LEFT_GUI) Keyboard.press(KEY_LEFT_GUI);
  
  // Ana tuşları işle
  if (macro.key1) Keyboard.press(macro.key1);
  if (macro.key2) Keyboard.press(macro.key2);
  if (macro.key3) Keyboard.press(macro.key3);
  
  // Tüm tuşları aynı anda yayınla
  Keyboard.releaseAll();
  
  // Hata ayıklama çıktısı
  Serial.print("Tuş kombinasyonu tetiklendi: Satır ");
  Serial.print(row + 1);
  Serial.print(", Sütun ");
  Serial.println(col + 1);
}
