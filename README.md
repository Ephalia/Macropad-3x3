# Arduino Pro Micro 3x3 HID Macropad Firmware

Arduino Pro Micro (ATmega32U4) kartı kullanarak geliştirilen 3x3 (dokuz tuş) özel macropad firmware'i. USB HID klavye ve medya kontrol cihazı olarak çalışır. Ses kontrolleri (Volume Up/Down/Mute), medya kontrolleri (Play/Pause/Previous/Next) ve sistem kısayollarını (Alt+F4, Win+D, Win+L) destekler. Yerleşik debouncing ile Windows, macOS ve Linux'ta sürücü gerekmeden tak-çalıştır çalışır.

## Özellikler

- **Arduino IDE ile yazılmış**: C++ dilinde, HID-Project kütüphanesi kullanılarak yazılmıştır
- **Arduino Pro Micro uyumlu**: ATmega32U4 çipli kartlar için geliştirilmiştir
- **3×3 buton ızgarası**: Toplam 9 bağımsız GPIO girişi
- **Medya kontrolleri**: Volume Up/Down/Mute, Play/Pause, Previous/Next desteği
- **Debouncing**: 15 ms debounce süresi ile tuş titremesini önler
- **Yapılandırılabilir makrolar**: Kolayca özelleştirilebilir tuş kombinasyonları
- **Plug-and-play**: USB HID cihazı olarak otomatik tanınır, sürücü gerekmez
- **Kapsamlı dokümantasyon**: Pin eşlemesi, kurulum ve kullanım talimatları

## Donanım Gereksinimleri

- **Arduino Pro Micro** (ATmega32U4 tabanlı)
- **9 × anlık basmalı düğme** (normalde açık - NO tipi)
- **Kablolama malzemeleri**: Her düğmeyi GPIO pini ile toprak (GND) arasına bağlamak için
- **USB kablosu**: Güç sağlama, programlama ve HID iletişimi için

## Pin Eşlemesi

Arduino Pro Micro'da düğmelerin GPIO pin atamalarını aşağıdaki tablo göstermektedir:

| Konumu | Satır | Sütun | GPIO Pin | Varsayılan Tuş Kombinasyonu |
|--------|-------|-------|----------|----------------------------|
| Sol Üst | 1 | 1 | D4 (A6) | **Ses Azalt** (Volume Down) |
| Üst Orta | 1 | 2 | D6 (A7) | **Ses Arttır** (Volume Up) |
| Sağ Üst | 1 | 3 | D10 | **Sesi Kapat** (Mute) |
| Sol Orta | 2 | 1 | D16 (A2) | **Önceki** (Previous) |
| Orta Merkez | 2 | 2 | D14 (A0) | **Play/Pause** |
| Sağ Orta | 2 | 3 | D15 (A1) | **Sonraki** (Next) |
| Sol Alt | 3 | 1 | D9 | **Alt + F4** (Uygulamayı Kapat) |
| Alt Orta | 3 | 2 | D5 | **Win + D** (Masaüstüne Git) |
| Sağ Alt | 3 | 3 | D3 | **Win + L** (Bilgisayarı Kilitle) |

### Arduino Pro Micro Pin Referansı

Arduino Pro Micro'nun fiziksel pin düzeni:

```
┌─────────────────────────────────────┐
│  USB    (GND)(RAW)                  │
├─────────────────────────────────────┤
│(GND) D13 D11 D9  D8  D7  D6  D5  D4│
│(VCC) (A0) D12 D10 D16 D14 D15(A1)  │
│      (A2)     (A3)        (A4)(A5) │
└─────────────────────────────────────┘

GND = Toprak pini (tüm düğmelerin diğer tarafına bağlansın)
```

## Kurulum ve Kullanım

### 1. Arduino IDE Yükleme

Arduino IDE'yi https://www.arduino.cc/en/software adresinden indirin ve yükleyin.

### 2. HID-Project Kütüphanesini Yükleme

**ÖNEMLİ:** Bu firmware medya kontrolleri için HID-Project kütüphanesine ihtiyaç duyar.

Arduino IDE'de:
1. **Taslak → Kütüphane Ekle → Kütüphaneleri Yönet** menüsüne gidin
2. Arama kutusuna "HID-Project" yazın
3. **HID-Project by NicoHood** kütüphanesini bulun ve **Yükle** butonuna tıklayın
4. En son sürümü yükleyin (önerilen: v2.8.4 veya üzeri)

### 3. Arduino Pro Micro Desteğinin Eklenmesi

Arduino IDE'de:
1. **Dosya → Tercihler** menüsüne gidin
2. **Ek Kartlar Yöneticisi URL'leri** alanına ekleyin:
   ```
   https://adafruit.github.io/arduino-board-support/package_adafruit_index.json
   ```
3. **Araçlar → Kart → Kart Yöneticisi** menüsüne gidin
4. "Arduino AVR Boards" veya "Adafruit AVR Boards" arayın
5. "Arduino Leonardo" (Arduino Pro Micro için de çalışır) yükleyin

### 4. Kart Seçimi ve Portu Ayarlama

1. **Araçlar → Kart** menüsünden **Arduino Leonardo** seçin
2. **Araçlar → Mikrodenetleyici** menüsünden **ATmega32U4** seçin
3. **Araçlar → Port** menüsünden Arduino'nun bağlı olduğu COM portunu seçin (örn. COM3, /dev/ttyACM0)

### 5. Firmware Yükleme

1. `HID_Macropad_3x3.ino` dosyasını Arduino IDE'de açın
2. **Taslak → Doğrula/Derle** ile derleme kontrolü yapın
3. **Taslak → Yükle** seçeneği ile firmware'i kartı yükleyin

### 6. Donanım Bağlantısı

Tuşlarınızı aşağıdaki şemaya göre bağlayın:

```
Tuş Switch A tarafı → GPIO Pin (yukarıdaki tablo)
Tuş Switch B tarafı → GND (toprak)
```

Her tuş için İngilizce "bistable" veya "momentary" tipi switch kullanabilirsiniz.

## Tuş Kombinasyonlarını Özelleştirme

### Makro Tanımlarını Düzenleme

`HID_Macropad_3x3.ino` dosyasında `MACRO_BINDINGS` dizisini düzenleyin. İki tür makro desteklenir:

1. **MACRO_KEYBOARD**: Klavye tuş kombinasyonları (Ctrl+C, Alt+F4, vb.)
2. **MACRO_CONSUMER**: Medya kontrol tuşları (Volume Up/Down, Play/Pause, vb.)

```cpp
const MacroKey MACRO_BINDINGS[3][3] = {
  // Klavye kombinasyonu örneği
  { { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'c', 0, 0 },     // Ctrl+C
    { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'v', 0, 0 },     // Ctrl+V
    { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'x', 0, 0 } },   // Ctrl+X
  // Medya kontrolü örneği
  { { MACRO_CONSUMER, 0, MEDIA_VOLUME_UP, 0, 0 },     // Ses Arttır
    { MACRO_CONSUMER, 0, MEDIA_PLAY_PAUSE, 0, 0 },    // Play/Pause
    { MACRO_CONSUMER, 0, MEDIA_NEXT, 0, 0 } },        // Sonraki
  // ... kalan tuşlar
};
```

### Desteklenen Modifier Tuşları

- `KEY_LEFT_CTRL` - Sol Ctrl
- `KEY_RIGHT_CTRL` - Sağ Ctrl
- `KEY_LEFT_SHIFT` - Sol Shift
- `KEY_RIGHT_SHIFT` - Sağ Shift
- `KEY_LEFT_ALT` - Sol Alt
- `KEY_RIGHT_ALT` - Sağ Alt
- `KEY_LEFT_GUI` - Windows/Command tuşu
- `KEY_RIGHT_GUI` - Sağ Windows tuşu

Birden fazla modifier'ı bitwise OR (`|`) operatörü ile birleştirebilirsiniz:
```cpp
KEY_LEFT_CTRL | KEY_LEFT_SHIFT  // Ctrl+Shift
```

### Desteklenen Tuş Kodları (Klavye)

Standart ASCII karakterler: `'a'`, `'b'`, ..., `'z'`, `'0'`, `'1'`, ...

Özel tuşlar (HID-Project kütüphanesinde tanımlı):
- `KEY_RETURN` - Enter
- `KEY_BACKSPACE` - Backspace
- `KEY_TAB` - Tab
- `KEY_SPACE` - Boşluk
- `KEY_CAPS_LOCK` - Caps Lock
- `KEY_PRINT_SCREEN` - Print Screen
- `KEY_PAGE_UP` - Page Up
- `KEY_PAGE_DOWN` - Page Down
- `KEY_HOME` - Home
- `KEY_END` - End
- `KEY_DELETE` - Delete
- `KEY_UP_ARROW` - Ok Yukarı
- `KEY_DOWN_ARROW` - Ok Aşağı
- `KEY_LEFT_ARROW` - Ok Sola
- `KEY_RIGHT_ARROW` - Ok Sağa
- `KEY_F1` - `KEY_F12` - F1 ile F12 tuşları

### Desteklenen Medya Kontrol Tuşları

HID-Project kütüphanesi aşağıdaki medya kontrollerini destekler:

**Ses Kontrolleri:**
- `MEDIA_VOLUME_UP` - Ses Arttır
- `MEDIA_VOLUME_DOWN` - Ses Azalt
- `MEDIA_VOLUME_MUTE` - Sesi Kapat/Aç

**Medya Oynatıcı Kontrolleri:**
- `MEDIA_PLAY_PAUSE` - Oynat/Duraklat
- `MEDIA_NEXT` - Sonraki Parça
- `MEDIA_PREVIOUS` - Önceki Parça
- `MEDIA_STOP` - Durdur

**Diğer Kontroller:**
- `CONSUMER_CALCULATOR` - Hesap Makinesi Aç
- `CONSUMER_EMAIL_READER` - E-posta Uygulaması Aç
- `CONSUMER_BROWSER_HOME` - Tarayıcı Ana Sayfa
- `CONSUMER_BROWSER_SEARCH` - Tarayıcı Arama

Tam liste için HID-Project kütüphanesinin dokümantasyonunu inceleyebilirsiniz.

### Örnek Konfigürasyonlar

#### Medya Kontrol Konfigürasyonu
```cpp
// Ses ve müzik kontrolleri
{ { MACRO_CONSUMER, 0, MEDIA_VOLUME_DOWN, 0, 0 },  // Ses Azalt
  { MACRO_CONSUMER, 0, MEDIA_VOLUME_UP, 0, 0 },    // Ses Arttır
  { MACRO_CONSUMER, 0, MEDIA_VOLUME_MUTE, 0, 0 } } // Sesi Kapat
```

#### Web Tarayıcı Kontrolleri
```cpp
// Sayfayı yenile
{ MACRO_KEYBOARD, KEY_LEFT_CTRL, 'r', 0, 0 }

// Yeni sekme aç
{ MACRO_KEYBOARD, KEY_LEFT_CTRL, 't', 0, 0 }

// Geçmiş sil
{ MACRO_KEYBOARD, KEY_LEFT_CTRL | KEY_LEFT_SHIFT, KEY_DELETE, 0, 0 }
```

#### Kod Editörü Kısayolları
```cpp
// Satırı sil (VS Code)
{ MACRO_KEYBOARD, KEY_LEFT_CTRL | KEY_LEFT_SHIFT, 'k', 0, 0 }

// Çift tıkla seç
{ MACRO_KEYBOARD, KEY_LEFT_CTRL, 'd', 0, 0 }

// Multi-line edit (VS Code)
{ MACRO_KEYBOARD, KEY_LEFT_CTRL | KEY_LEFT_ALT, KEY_UP_ARROW, 0, 0 }
```

#### Sistem Kısayolları
```cpp
// Ekran görüntüsü (Windows)
{ MACRO_KEYBOARD, 0, KEY_PRINT_SCREEN, 0, 0 }

// Görev Yöneticisi (Windows)
{ MACRO_KEYBOARD, KEY_LEFT_CTRL | KEY_LEFT_SHIFT, KEY_ESC, 0, 0 }

// Spotlight Arama (Mac)
{ MACRO_KEYBOARD, KEY_LEFT_GUI, KEY_SPACE, 0, 0 }
```

## Debouncing Stratejisi

Firmware 1 ms aralıklarla tüm düğmeleri tarar. Bir düğmedeki durumu değişikliği tespit edildiğinde:
1. Durum değişiminin zamanı kaydedilir
2. 15 ms geçmesini bekler
3. Durum halen değişmişse, basma/bırakma olayı olarak kaydedilir

Bu yaklaşım, anahtar sıçramasından kaynaklanabilecek hatalı tetiklemeleri etkili bir şekilde filtreler.

## Sorun Giderme

| Sorun | Olası Nedenleri | Çözüm |
|-------|-----------------|--------|
| Cihaz algılanmıyor | USB bağlantısı, sürücü | USB kablosunu değiştirin, kartı yeniden başlatın |
| Düğmeler yanıt vermiyor | Pin bağlantısı, yazılım | Pin konfigürasyonunu kontrol edin, seri monitörü açarak hata ayıklayın |
| Düğmeler birden fazla basılı gözüküyor | Debounce süresi | `DEBOUNCE_TIME` değerini artırın (örn. 20 ms) |
| Modifiyer tuşlar çalışmıyor | Syntax hatası | `MACRO_BINDINGS` dizisindeki syntax'ı kontrol edin |
| Arduino IDE'de yükleme hatası | Kart/port seçimi | Doğru kart (Leonardo) ve portu seçili olduğundan emin olun |

## Seri Monitörü ile Hata Ayıklama

Arduino IDE'de **Araçlar → Seri Monitörü** açın (hız: 9600 baud). Firmware aşağıdakine benzer mesajlar gösterecektir:

```
Arduino Pro Micro 3x3 Macropad başlatılıyor...
Macropad başarıyla başlatıldı!
Tuş kombinasyonu tetiklendi: Satır 1, Sütun 1
```

## Dosya Yapısı

```
.
├── HID_Macropad_3x3.ino          # Ana Arduino sketch dosyası
├── README.md                      # Bu dokümantasyon (Türkçe)
├── docs/
│   └── pin_mapping.md            # Detaylı pin eşlemesi ve kablolama şeması
└── examples/
    ├── example_productivity.ino   # Verimlilik makroları örneği
    ├── example_gaming.ino         # Oyun makroları örneği
    └── example_media.ino          # Medya kontrol makroları örneği
```

## Güvenlik ve Uyarılar

⚠️ **Güvenlik Uyarıları:**
- USB HID cihazı olarak çalıştığı için, tuş kombinasyonları yetkisiz kişiler tarafından tetiklenebilir. Güvenlik açısından hassas kombinasyonları kaydetmeyin.
- Bilgisayarın USB portlarını kilitlemek, bu riski azaltır.
- Halka açık bilgisayarlarda macropad kullanmayın.

## Lisans

Bu proje MIT Lisansı altında sağlanmıştır. Kendi macropad projeleriniz için serbestçe değiştirebilir ve kullanabilirsiniz.

## Kaynaklar

- [Arduino Resmi Websitesi](https://www.arduino.cc)
- [Arduino Pro Micro Dokümantasyon](https://www.arduino.cc/en/Main/ArduinoBoardProMicro)
- [HID-Project Kütüphanesi (NicoHood)](https://github.com/NicoHood/HID)
- [HID-Project Dokümantasyon](https://github.com/NicoHood/HID/wiki)
- [Arduino Keyboard Kütüphanesi Referansı](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/)

## Destek ve Katkı

Sorularınız, önerileriniz veya hata raporları için GitHub repository'sinde issue açabilirsiniz.

Kod geliştirmeleri için:
1. Repository'yi fork edin
2. Yeni bir branch oluşturun (`git checkout -b feature/iyilestirme`)
3. Değişikliklerinizi commit edin (`git commit -am 'Iyilestirme açıklaması'`)
4. Branch'inizi push edin (`git push origin feature/iyilestirme`)
5. Pull Request oluşturun

---

**Son güncelleme**: 2024
**Versyon**: 1.0
