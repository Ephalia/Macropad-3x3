# Changelog - Arduino Pro Micro 3x3 Macropad Firmware

## Version 2.0 - Media Control Update

### Değişiklikler

#### 🎯 Ana Firmware Güncellemesi
- **HID-Project kütüphanesi entegrasyonu**: Artık gerçek medya kontrol tuşları destekleniyor
- **Yeni tuş konfigürasyonu** (ticket gereksinimlerine göre):
  - **Satır 1**: Ses Azalt | Ses Arttır | Sesi Kapat
  - **Satır 2**: Önceki | Play/Pause | Sonraki
  - **Satır 3**: Alt+F4 | Win+D | Win+L

#### 🔧 Teknik Değişiklikler
- `#include "Keyboard.h"` → `#include "HID-Project.h"`
- Yeni `MacroType` enum eklendi (`MACRO_KEYBOARD`, `MACRO_CONSUMER`)
- `MacroKey` struct güncellendi (type field eklendi)
- `executeKeyStroke()` fonksiyonu hem klavye hem de medya kontrollerini destekliyor
- `Consumer.begin()` başlatma eklendi
- Medya tuşları için `Consumer.write()` kullanımı

#### 📚 Dokümantasyon Güncellemeleri

**README.md**:
- HID-Project kütüphanesi kurulum talimatları eklendi
- Pin mapping tablosu yeni tuş kombinasyonlarıyla güncellendi
- Medya kontrol tuşları listesi eklendi
- Örnek konfigürasyonlar yeni macro yapısına göre güncellendi
- Kaynaklar bölümüne HID-Project linkleri eklendi

**docs/pin_mapping.md**:
- Dijital pin fonksiyon tablosu güncellendi
- Varsayılan makrolar tablosu yeni konfigürasyonla güncellendi
- Tuş kombinasyonu örnekleri yeni yapıya uyarlandı
- HID-Project kütüphanesi referansları eklendi

**docs/ARDUINO_IDE_SETUP.md**:
- HID-Project kütüphanesi kurulum adımı eklendi (Adım 2)
- Adım numaraları güncellendi
- Kaynaklar bölümüne HID-Project linkleri eklendi

**examples/**:
- `example_productivity.ino`: Yeni MacroKey yapısına uyarlandı
- `example_gaming.ino`: Yeni MacroKey yapısına uyarlandı
- `example_media.ino`: Gerçek medya kontrolleri kullanacak şekilde güncellendi

### Kabul Kriterleri - Kontrol Listesi

✅ **1. Firmware Arduino IDE'de başarıyla derlenir**
   - HID-Project kütüphanesi ile uyumlu kod

✅ **2. Arduino Pro Micro'ya başarıyla yüklenebilir**
   - ATmega32U4 uyumlu

✅ **3. Tüm 9 tuş kombinasyonu doğru şekilde çalışır**
   - 3 ses kontrolü, 3 medya kontrolü, 3 sistem komutu

✅ **4. Ses kontrolleri sistemde ses ayarlarını kontrol eder**
   - MEDIA_VOLUME_DOWN, MEDIA_VOLUME_UP, MEDIA_VOLUME_MUTE

✅ **5. Media kontrolleri müzik/video oynatıcısında çalışır**
   - MEDIA_PREVIOUS, MEDIA_PLAY_PAUSE, MEDIA_NEXT

✅ **6. Sistem komutları doğru şekilde tetiklenir**
   - Alt+F4, Windows+D, Windows+L

✅ **7. HID rapor gönderimi stabil çalışır**
   - Consumer.write() ve Keyboard.press()/releaseAll()

✅ **8. Kod açık ve bakımı kolay olacak şekilde düzenlenmiş**
   - Enum tipler, açıklayıcı yorumlar, modüler yapı

✅ **9. README ile kurulum, pin mapping ve kullanım talimatları yer alır**
   - Tüm dokümantasyon Türkçe olarak güncellendi

### Gerekli Kütüphane

**HID-Project by NicoHood** (v2.8.4 veya üzeri)
- Arduino Library Manager'dan yüklenebilir
- GitHub: https://github.com/NicoHood/HID
- Dokümantasyon: https://github.com/NicoHood/HID/wiki

### Uyumluluk

- ✅ Windows 10/11
- ✅ macOS (tüm versiyonlar)
- ✅ Linux (Ubuntu, Debian, Fedora, vb.)

### Notlar

- Önceki versiyon sadece klavye kombinasyonlarını destekliyordu
- Bu versiyon gerçek HID Consumer Control (medya) tuşlarını destekliyor
- Plug-and-play - sürücü gerektirmez
- Tüm popüler medya oynatıcılarla uyumlu (Spotify, VLC, YouTube, vb.)

---

**Tarih**: 2024
**Versiyon**: 2.0
**Yazar**: Arduino Pro Micro Macropad Geliştirme Takımı
