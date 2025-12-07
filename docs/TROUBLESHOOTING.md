# Arduino Pro Micro 3x3 Macropad - Sorun Giderme Kılavuzu

Bu dokümantasyon, Arduino Pro Micro 3x3 Macropad'i kullanırken yaşanabilecek yaygın sorunların çözüm yollarını içerir.

## Genel Sorunlar

### 1. Cihaz algılanmıyor / Bağlanmıyor

**Belirtiler:**
- Arduino IDE'de "Port" seçeneğinde hiçbir şey görünmüyor
- İşletim sistemi Arduino Pro Micro'yu tanımıyor
- USB bağlantısı yapılı olmasına rağmen cihaz algılanmıyor

**Çözüm Adımları:**

1. **USB Kablosunu Kontrol Edin**
   ```
   ✓ Veri kablosu mu? (sadece şarj değil)
   ✓ Kablonun sağlam olduğundan emin olun
   ✓ Farklı bir USB portunu deneyiniz
   ✓ Kabloyı çıkartıp 5 saniye sonra takınız
   ```

2. **Arduino IDE Ayarlarını Kontrol Edin**
   - **Araçlar → Kart**: Arduino Leonardo veya Adafruit Pro Micro seçili mi?
   - **Araçlar → Processor**: ATmega32U4 seçili mi?
   - Arduino IDE'yi kapatıp yeniden açın

3. **İşletim Sistemi Düzeyinde Kontrol (Windows)**
   - Cihaz Yöneticisi'ni açın
   - "Bilinmeyen cihaz" altında Arduino Pro Micro var mı?
   - Varsa, sağ tık → "Sürücüyü Güncelle" → "Bilgisayarımı tara"

4. **İşletim Sistemi Düzeyinde Kontrol (Linux)**
   ```bash
   # Terminal'de aşağıdakileri çalıştırın:
   lsusb
   # VID 2341 (Arduino) ve PID 8037 (Pro Micro) arayan
   
   ls /dev/ttyACM* /dev/ttyUSB*
   # Mevcut seri portları listele
   ```

5. **Bootloader Problemi (Son Çare)**
   - Arduino Pro Micro üzerindeki RESET düğmesine iki kez hızlı tıklayın
   - LED'ler hızlı yanıp sönmeye başlarsa bootloader modunda
   - Hemen Arduino IDE'de yükleme işlemi yapın

---

### 2. Firmware yükleme başarısız

**Belirtiler:**
- "Yükleme başarısız" hatası
- "stk500_recv(): programmer is not responding" hatası
- Yükleme işlemi asılı kalıyor

**Çözüm Adımları:**

1. **Bağlantıyı Yenileyin**
   ```
   1. USB kablosunu çıkartın
   2. Arduino IDE'yi kapatın
   3. 10 saniye bekleyin
   4. Arduino IDE'yi yeniden açın
   5. USB'yi takın
   ```

2. **Doğru Port'u Seçin**
   - **Araçlar → Port** menüsünde doğru COM/ttyACM portunu seçin
   - Eğer birden fazla port varsa, baştan itibaren hepsini deneyin

3. **Bootloader Moduna Gir**
   - Arduino Pro Micro üzerindeki RESET düğmesini bulun
   - İki kez hızlı tıklayın (1 saniye arayla)
   - LED'ler yanıp söneceğini (bootloader modu)
   - Hemen Arduino IDE'de **Taslak → Yükle** yapın

4. **Kart Ayarlarını Kontrol Edin**
   - **Araçlar → Kart**: Arduino Leonardo veya Adafruit Pro Micro
   - **Araçlar → Processor**: ATmega32U4 (5V, 16MHz)
   - **Araçlar → Upload Speed**: 57600 olarak ayarlayın

5. **Verbose Çıktı Etkinleştir**
   - **Dosya → Tercihleri** açın
   - "Upload verbose" ve "Compile verbose" seçeneklerini işaretleyin
   - Tekrar yüklemeyi deneyin ve hatanın tam mesajını okuyun

---

## Donanım / Kablolama Sorunları

### 3. Tuşlar algılanmıyor / Yanıt vermiyor

**Belirtiler:**
- Tuşlara basılıyor ama hiçbir şey olmadığı
- Sadece bazı tuşlar çalışıyor
- Seri monitörde "Tuş tetiklendi" mesajı görünmüyor

**Kontrol Listesi:**

1. **Kablolama Doğruluğu**
   ```
   ✓ Her tuş, GPIO pininin bir ucundan ve GND'nin diğer ucundan bağlıdır
   ✓ GND pinleri birbirine bağlı mı? (tüm tuşlar aynı GND'ye bağlanmalı)
   ✓ GPIO pinleri doğru mu? (D4, D6, D10, vb.)
   ✓ Açık devreler (kesili kablolar) yok mu?
   ```

2. **Pin Konfigürasyonunu Kontrol Edin**
   
   İlk olarak hangi tuşların çalışmadığını belirleyin. `.ino` dosyasında:
   ```cpp
   const int BUTTON_PINS[3][3] = {
     { 4,  6, 10 },   // Satır 1
     { 16, 14, 15 },  // Satır 2
     { 9, 5, 3 }      // Satır 3
   };
   ```
   
   Bu pinlerin, tuşların bağlı olduğu pinlerle eşleşip eşleşmediğini kontrol edin.

3. **Seri Monitör ile Hata Ayıklama**
   ```
   1. Arduino IDE'de Araçlar → Seri Monitörü aç
   2. Baud rate: 9600 olarak ayarla
   3. Başlangıç mesajlarını gör: "Macropad başarıyla başlatıldı!"
   4. Tuşlara basıp mesajları gözlemle
   ```

4. **Pull-Up Dirençlerini Kontrol Edin**
   
   Eğer tuşlar terste davranıyorsa (basılı gözüküyor, basılmamışken):
   ```cpp
   // updateButtonState() fonksiyonunda kontrol edin:
   int reading = digitalRead(pin);
   // Eğer mantık terste ise, HIGH ve LOW'u değiştirin
   ```

5. **Debounce Süresini Ayarlayın**
   
   Eğer tuşlar çok sensitif:
   ```cpp
   const unsigned long DEBOUNCE_TIME = 20;  // 15ms yerine 20ms
   ```

---

### 4. Tutarsız tuş tetiklemesi

**Belirtiler:**
- Bazen tuş çalışıyor, bazen çalışmıyor
- Aynı tuş farklı zamanlarda farklı davranıyor
- Rastgele tuş kombinasyonları tetikleniyor

**Çözüm Adımları:**

1. **Kablolama Kalitesini Kontrol Edin**
   ```
   ✓ Gevşek bağlantılar var mı? (yakından kontrol edin)
   ✓ Kablolama güvenli mi? (lehim, bağlantı iyileştirmeleri)
   ✓ Elektromanyetik parazit kaynağı var mı? (wi-fi routeri, mikrodalgası)
   ```

2. **Debounce Mantığını İyileştirin**
   ```cpp
   const unsigned long DEBOUNCE_TIME = 25;  // 25ms'ye artırın
   ```

3. **Seri Monitörü ile Detaylı Hata Ayıklama**
   ```cpp
   // updateButtonState() fonksiyonunun başına ekleyin:
   Serial.print("Pin ");
   Serial.print(pin);
   Serial.print(" reading: ");
   Serial.println(reading);
   ```

---

## Yazılım / Makro Sorunları

### 5. Tuş kombinasyonları yanlış tetikleniyor

**Belirtiler:**
- Ctrl+C yerine C tuşu gidiyor
- Modifier tuşlar çalışmıyor
- Bazı karakter kombinasyonları çıkarmıyor

**Çözüm Adımları:**

1. **Makro Tanımını Kontrol Edin**
   ```cpp
   // MACRO_BINDINGS dizisinde syntax hataları var mı?
   // Örneğin, virgül eksikliği, parantez hataları?
   
   // Doğru Syntax:
   { { KEY_LEFT_CTRL, 'c', 0, 0 },
   
   // Yanlış Syntax:
   { KEY_LEFT_CTRL, 'c', 0, 0 },  // Fazladan { eksik
   ```

2. **Modifier Tuş Tanımlarını Kontrol Edin**
   ```cpp
   // Desteklenen modifier tuşlar:
   KEY_LEFT_CTRL       // Sol Ctrl
   KEY_RIGHT_CTRL      // Sağ Ctrl
   KEY_LEFT_SHIFT      // Sol Shift
   KEY_RIGHT_SHIFT     // Sağ Shift
   KEY_LEFT_ALT        // Sol Alt
   KEY_RIGHT_ALT       // Sağ Alt
   KEY_LEFT_GUI        // Windows/Command
   KEY_RIGHT_GUI       // Sağ Windows
   
   // Birden fazla modifier:
   KEY_LEFT_CTRL | KEY_LEFT_SHIFT  // Ctrl+Shift
   ```

3. **Karekter Kodlarını Kontrol Edin**
   ```cpp
   // Harf (küçük):
   'a', 'b', 'c'  // ✓ Doğru
   'A', 'B', 'C'  // ✗ Yanlış (büyük harf olarak tanımlanmaz)
   
   // Özel Tuş:
   KEY_RETURN     // Enter
   KEY_BACKSPACE  // Backspace
   KEY_TAB        // Tab
   KEY_ESC        // Escape
   ```

4. **ASCII Arama Tablosu**
   ```cpp
   '0' - '9'      // Rakamlar
   'a' - 'z'      // Harfler (sadece küçük)
   ' '            // Boşluk
   '!'            // !
   '@'            // @
   // vb...
   ```

---

### 6. Hiçbir makro tetiklenmiyor

**Belirtiler:**
- Tuşlar basılıyor ama bilgisayar cevap vermiyor
- Seri monitörde "Tuş tetiklendi" mesajı görülüyor ama bilgisayar tuş almıyor

**Kontrol Listesi:**

1. **Firmware Yükleme Kontrolü**
   ```
   ✓ Firmware başarıyla yüklendi mi?
   ✓ Seri monitörde başlangıç mesajları görülüyor mu?
   ```

2. **USB HID Başlatma Kontrolü**
   ```cpp
   // main setup() fonksiyonunda şu satır var mı?
   Keyboard.begin();
   ```

3. **Operatif Sistem HID Cihazını Tanıyor mu?**
   - Windows: Cihaz Yöneticisi'nde kontrol edin
   - macOS: Sistem Tercihleri → Güvenlik
   - Linux: `lsusb` veya `cat /proc/bus/input/devices`

4. **Farklı Uygulamada Test Edin**
   - Metin Düzenleyiciyi aç (Notepad, VS Code, vb.)
   - Tuşlara basıp metni yazılıyor mu?

---

## Performans Sorunları

### 7. Anahtar Titremesi (Multiple Presses)

**Belirtiler:**
- Bir tuşa bir kez basılıyor ama iki veya daha fazla tuş okuması tetikleniyor
- Hızlı ve tekrarlayan tuş olayları

**Çözüm Adımları:**

1. **Debounce Süresini Artırın**
   ```cpp
   const unsigned long DEBOUNCE_TIME = 20;  // 15ms yerine 20ms
   // Eğer sorun devam ederse 30ms deneyin
   ```

2. **Tuş Kalitesini Kontrol Edin**
   ```
   ✓ Kullanılan tuş mekanik olarak iyi mi?
   ✓ Tuş birkaç yüz kez basılarak test edildi mi?
   ✓ Kontaklar temiz mi?
   ```

3. **Kablolama Kontrolü**
   ```
   ✓ Gevşek bağlantılar var mı?
   ✓ Elektromanyetik parazit kaynağı var mı?
   ✓ Kablolama shielded (korummalı) mı?
   ```

---

### 8. Latency (Gecikmeli Yanıt)

**Belirtiler:**
- Tuşa basıldıktan sonra gecikme var
- Çok yavaş tuş tetiklemesi

**Çözüm Adımları:**

1. **Tarama Aralığını Azaltın**
   ```cpp
   const unsigned long SCAN_INTERVAL = 1;  // 1ms
   // Zaten minimize edilmiş, daha az yapılamaz
   ```

2. **Diğer Kodlardan Engel Kontrolü**
   - Loop döngüsünde `delay()` kullanımı var mı? (KESINLIKLE YAPMAYINIZ)
   - `Serial.print()` çok sık çağrılıyor mu?

3. **Debounce Süresini Kontrol Edin**
   ```cpp
   const unsigned long DEBOUNCE_TIME = 15;  // Azaltın
   // Fakat anahtar titremesi yaratmayacak seviyede
   ```

---

## Arduino IDE Sorunları

### 9. Derleme (Compile) Hataları

**Belirtiler:**
- Arduino IDE'de "Derlemesi başarısız" hatası
- Çıkış penceresinde kırmızı hata mesajları

**Ortak Hatalar:**

| Hata | Nedeni | Çözüm |
|------|--------|-------|
| `error: invalid type arg...` | Tanımlama hatası | Virgül eksikliğini kontrol edin |
| `error: expected '}' before...` | Parantez/ayraç hatası | Ayraçların eşleştiğini kontrol edin |
| `error: 'KEY_LEFT_CTRL' was not declared` | Kütüphane eksikliği | `#include "Keyboard.h"` var mı? |
| `error: conflicting declaration` | Değişken çakışması | Aynı adlı değişken var mı? |

**Hata Mesajını Okuyun:**
```
error: invalid types 'int[int]' for array subscript
  at HID_Macropad_3x3.ino:XX:YY
```

Satır numarası (XX) belirtilir, o satırı kontrol edin.

---

### 10. Upload Hataları

**Belirtiler:**
- Derleme başarılı fakat yükleme başarısız
- "avrdude: stk500_recv(): programmer is not responding"

**Çözüm:**
- Bkz: Sorun #2 (Firmware yükleme başarısız)

---

## Sistem Spesifik Sorunlar

### 11. Windows'ta Sürücü Sorunu

**Belirtiler:**
- Arduino Pro Micro görülüyor ama "Bilinmeyen Cihaz"
- COM portu atanamıyor

**Çözüm:**
1. Cihaz Yöneticisi'ni açın
2. "Bilinmeyen Cihaz" üzerine sağ tık
3. "Sürücüyü Güncelle" seçin
4. "Bilgisayarımı tara" seçin
5. Sürücü bulunup yüklenecektir

### 12. macOS'ta Sürücü Sorunu

**Belirtiler:**
- Arduino IDE'de port görülmüyor
- Bağlantı kurulamıyor

**Çözüm:**
```bash
# Terminal'de aşağıdakileri çalıştırın:
ls /dev/cu.*      # Tüm seri portları listele
ls -la /dev | grep usbmodem  # USB seri portları ara

# Eğer /dev/cu.usbmodem* var ise cihaz tanınmıştır
```

### 13. Linux'ta Port Erişim Sorunu

**Belirtiler:**
- "Permission denied" hatası
- Arduino IDE'de port seçilemiyor

**Çözüm:**
```bash
# Kullanıcıyı dialout grubuna ekleyin:
sudo usermod -a -G dialout $USER

# Sonrasında çıkış yapıp yeniden giriş yapın veya:
newgrp dialout

# Port izinlerini kontrol edin:
ls -la /dev/ttyACM*
```

---

## İleri Hata Ayıklama

### Seri Monitörle Detaylı Kontrol

```cpp
// Hata ayıklama modunu etkinleştirmek için:

#define DEBUG 1  // Dosyanın başına ekleyin

#ifdef DEBUG
  #define DPRINT(x) Serial.print(x)
  #define DPRINTLN(x) Serial.println(x)
#else
  #define DPRINT(x)
  #define DPRINTLN(x)
#endif

// Kullanım:
DPRINTLN("Debug mesajı");
```

### Manual Test Kodu

```cpp
// Tüm pinleri test etmek için:
void testAllPins() {
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      int pin = BUTTON_PINS[row][col];
      int state = digitalRead(pin);
      Serial.print("Pin ");
      Serial.print(pin);
      Serial.print(" Durum: ");
      Serial.println(state);
    }
  }
}

// Loop'a ekleyin:
// Belirli zaman aralıklarında çalıştır
```

---

## Kontrol Listesi (Baştan Başlama)

Eğer hiçbir çözüm işe yaramazsa, baştan başlamayı deneyin:

- [ ] Firmware'i tamamen sil
- [ ] Arduino IDE'yi tamamen kaldır ve yeniden kur
- [ ] Arduino Pro Micro'yu yenile (bootloader'ı reset et)
- [ ] Yeni bir `.ino` dosyası oluştur
- [ ] Kodu adım adım yeniden yaz
- [ ] Test et

---

## İletişim ve Destek

Sorununuzu çözemezseniz:

1. GitHub Repository'sinde Issue açın
2. Şu bilgileri sağlayın:
   - İşletim Sistemi (Windows/macOS/Linux)
   - Arduino IDE Versiyonu
   - Arduino Pro Micro Versiyonu
   - Hata Mesajı (tam metin)
   - Seri Monitör Çıktısı
   - Yaptığınız Değişiklikler

---

**Son Güncelleme**: 2024
**Versiyon**: 1.0
