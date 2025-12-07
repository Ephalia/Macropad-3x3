# Arduino Pro Micro 3x3 HID Macropad Firmware

Arduino Pro Micro (ATmega32U4) kartı kullanarak geliştirilen 3x3 (dokuz tuş) özel macropad firmware'i. USB HID klavye ve medya kontrol cihazı olarak çalışır. Ses kontrolleri (Volume Up/Down/Mute), medya kontrolleri (Play/Pause/Previous/Next) ve sistem kısayollarını (Alt+F4, Win+D, Win+L) destekler. Yerleşik debouncing ile Windows, macOS ve Linux'ta sürücü gerekmeden tak-çalıştır çalışır.

**🎯 ÖNEMLİ:** Bu firmware hem **diyotsuz** hem de **diyötlü** kurulumları destekler! Tercih ettiğiniz kurulum yöntemini seçebilirsiniz.

## Özellikler

- **Arduino IDE ile yazılmış**: C++ dilinde, HID-Project kütüphanesi kullanılarak yazılmıştır
- **Arduino Pro Micro uyumlu**: ATmega32U4 çipli kartlar için geliştirilmiştir
- **3×3 buton ızgarası**: Toplam 9 bağımsız GPIO girişi (D0-D8)
- **Medya kontrolleri**: Volume Up/Down/Mute, Play/Pause, Previous/Next desteği
- **Debouncing**: 20 ms debounce süresi ile tuş titremesini önler (20-50ms arası ayarlanabilir)
- **Yapılandırılabilir makrolar**: Kolayca özelleştirilebilir tuş kombinasyonları
- **Plug-and-play**: USB HID cihazı olarak otomatik tanınır, sürücü gerekmez
- **İki kurulum seçeneği**: Diyotsuz (basit) veya diyötlü (profesyonel) kurulum
- **Kapsamlı dokümantasyon**: Pin eşlemesi, kurulum ve kullanım talimatları

## Donanım Gereksinimleri

### Temel Bileşenler (Her İki Kurulum İçin)

- **Arduino Pro Micro** (ATmega32U4 tabanlı) × 1
- **Mekanik switch'ler** (Blue, Red, Brown vb.) veya tact switch'ler × 9
- **Jumper kablolar** (M-M, M-F) - 15-20 adet
- **Breadboard** veya özel PCB × 1
- **USB kablosu** (Micro-USB veya USB-C, kartınıza uygun) × 1

### Opsiyonel Bileşenler (Sadece Diyötlü Kurulum İçin)

- **1N4148 diyotlar** × 9 (kısa devre koruması için)

## Pin Eşlemesi

Arduino Pro Micro'da düğmelerin GPIO pin atamalarını aşağıdaki tablo göstermektedir:

| Konumu | Satır | Sütun | GPIO Pin | Varsayılan Tuş Kombinasyonu |
|--------|-------|-------|----------|----------------------------|
| Sol Üst | 1 | 1 | **D0** (RX) | **Ses Azalt** (Volume Down) |
| Üst Orta | 1 | 2 | **D1** (TX) | **Ses Arttır** (Volume Up) |
| Sağ Üst | 1 | 3 | **D2** (SDA) | **Sesi Kapat** (Mute) |
| Sol Orta | 2 | 1 | **D3** | **Önceki** (Previous) |
| Orta Merkez | 2 | 2 | **D4** | **Play/Pause** |
| Sağ Orta | 2 | 3 | **D5** | **Sonraki** (Next) |
| Sol Alt | 3 | 1 | **D6** | **Alt + F4** (Uygulamayı Kapat) |
| Alt Orta | 3 | 2 | **D7** | **Win + D** (Masaüstüne Git) |
| Sağ Alt | 3 | 3 | **D8** | **Win + L** (Bilgisayarı Kilitle) |

### Arduino Pro Micro Pin Referansı

Arduino Pro Micro'nun fiziksel pin düzeni:

```
┌─────────────────────────────────────┐
│         USB PORT (Micro/Type-C)     │
├─────────────────────────────────────┤
│ (TX) D1   RAW                       │
│ (RX) D0   GND                       │
│      GND  RST                       │
│      GND  VCC                       │
│(SDA) D2   A3                        │
│(SCL) D3   A2                        │
│      D4   A1                        │
│      D5   A0                        │
│      D6   D15                       │
│      D7   D14                       │
│      D8   D16                       │
│      D9   D10                       │
└─────────────────────────────────────┘

Kullanılan Pinler: D0, D1, D2, D3, D4, D5, D6, D7, D8
GND = Toprak pini (tüm switch'lerin ortak bağlantısı)
```

## Donanım Kurulum Seçenekleri

Bu macropad'i iki farklı şekilde kurabilirsiniz. Her iki yöntem de aynı firmware ile çalışır.

### ⚙️ SEÇENEK 1: DİYOTSUZ KURULUM (Basit)

**Kablolama Şeması:**
```
Switch Pin 1 ---------> GPIO Pin (D0-D8)
Switch Pin 2 ---------> GND (Ortak Toprak)
```

**Görsel Kablolama (Örnek - 1 Switch):**
```
Arduino Pro Micro          Mekanik Switch
    ┌────────┐                ┌──┐
    │        │                │  │
    │   D0   ├────────────────┤ 1│  (Switch Pin 1)
    │        │                │  │
    │   GND  ├────────────────┤ 2│  (Switch Pin 2)
    │        │                └──┘
    └────────┘
```

**Avantajları:**
- ✅ Daha basit ve hızlı kurulum
- ✅ Daha az kablo ve bileşen
- ✅ Maliyet düşük (diyot gerekmez)
- ✅ 3x3 gibi küçük kurulumlar için yeterli
- ✅ Breadboard projeleri için ideal

**Dezavantajları:**
- ⚠️ Kısa devre riskine karşı biraz daha hassas
- ⚠️ Matrix keyboard'a geçişte yeniden kablolama gerekir

**Kimler İçin Uygun:**
- Yeni başlayanlar
- Prototip ve test amaçlı projeler
- Basit ve hızlı kurulum isteyenler

---

### ⚙️ SEÇENEK 2: DİYÖTLÜ KURULUM (Profesyonel)

**Kablolama Şeması:**
```
Switch Pin 1 ---------> 1N4148 Diyot Katodu [-]
Diyot Anodu [+] ------> GPIO Pin (D0-D8)
Switch Pin 2 ---------> GND (Ortak Toprak)
```

**Görsel Kablolama (Örnek - 1 Switch):**
```
Arduino Pro Micro       1N4148 Diyot      Mekanik Switch
    ┌────────┐          ┌─────────┐          ┌──┐
    │        │          │ [-] [+] │          │  │
    │   D0   ├──────────┤  K   A  ├──────────┤ 1│
    │        │          └─────────┘          │  │
    │   GND  ├──────────────────────────────┤ 2│
    │        │                               └──┘
    └────────┘

NOT: K = Katot (kısa bacak, -), A = Anot (uzun bacak, +)
```

**Diyot Bağlantı Kuralları:**
1. **Diyot yönü ÖNEMLİ:** Katot (-) switch'e, anot (+) GPIO'ya bağlanmalı
2. **Katot tespiti:** Diyot üzerinde bantlı taraf, veya kısa bacak
3. **Anot tespiti:** Uzun bacak, veya bantsız taraf
4. **Test:** Multimetre ile diyot yönünü kontrol edebilirsiniz

**Avantajları:**
- ✅ Kısa devre koruması (ghosting tamamen önlenir)
- ✅ Daha güvenli ve profesyonel
- ✅ Matrix keyboard'a kolay geçiş
- ✅ Büyük projelere hazırlık
- ✅ Elektriksel parazitlerden korunma

**Dezavantajları:**
- ⚠️ Biraz daha karmaşık kurulum
- ⚠️ Ek maliyet (9 adet 1N4148 diyot)
- ⚠️ Daha fazla kablo ve bileşen

**Kimler İçin Uygun:**
- Profesyonel projeler
- Uzun süreli kullanım
- Güvenlik ve dayanıklılık önceliği olanlar
- İleride matrix keyboard yapmayı düşünenler

---

### 🔧 Fiziksel Montaj Adımları (Genel)

#### Breadboard Kurulumu:

1. **Arduino'yu yerleştirin**: Pro Micro'yu breadboard'un ortasına yerleştirin
2. **GND rail'i hazırlayın**: Breadboard'un GND rail'ini Arduino'nun GND pinine bağlayın
3. **Her switch için** (seçtiğiniz versiyona göre):

   **Diyotsuz Versiyon:**
   - Switch'in bir ayağını breadboard'a yerleştirin
   - Bu ayağı jumper kablo ile ilgili GPIO pinine (D0-D8) bağlayın
   - Switch'in diğer ayağını GND rail'ine bağlayın

   **Diyötlü Versiyon:**
   - Switch'in bir ayağını breadboard'a yerleştirin
   - 1N4148 diyotun katodunu (-) switch'in bu ayağına bağlayın
   - Diyotun anodunu (+) ilgili GPIO pinine (D0-D8) bağlayın
   - Switch'in diğer ayağını GND rail'ine bağlayın

4. **Bağlantıları kontrol edin**: Her pin ve GND bağlantısını test edin
5. **USB kablosunu bağlayın**: Arduino'yu bilgisayara bağlayın

### 🔍 Hangi Setup'ı Seçmelisiniz?

| Kriter | Diyotsuz | Diyötlü |
|--------|----------|---------|
| **Basitlik** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **Maliyet** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ |
| **Güvenlik** | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| **Profesyonellik** | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| **Gelecek Uyumluluk** | ⭐⭐ | ⭐⭐⭐⭐⭐ |

**Önerimiz:**
- **İlk deneyiminizse**: Diyotsuz başlayın, sonra diyötlü'ye geçin
- **Kalıcı proje ise**: Diyötlü kurulum yapın
- **Bütçe kısıtlı ise**: Diyotsuz yeterli

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

**Seçtiğiniz kurulum yöntemine göre bağlantı yapın:**

**Diyotsuz Kurulum için:**
```
Switch Pin 1 → GPIO Pin (D0-D8, yukarıdaki tabloya bakın)
Switch Pin 2 → GND (ortak toprak)
```

**Diyötlü Kurulum için:**
```
Switch Pin 1 → 1N4148 Diyot Katodu (-)
Diyot Anodu (+) → GPIO Pin (D0-D8, yukarıdaki tabloya bakın)
Switch Pin 2 → GND (ortak toprak)
```

**Not:** Her tuş için "momentary" (anlık basmalı) tipi switch kullanın. Mekanik veya tact switch'ler uygun olur.

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

Firmware 1 ms aralıklarla tüm düğmeleri tarar. Bir düğmedeki durum değişikliği tespit edildiğinde:
1. Durum değişiminin zamanı kaydedilir
2. 20 ms geçmesini bekler (varsayılan, 20-50ms arası ayarlanabilir)
3. Durum halen değişmişse, basma/bırakma olayı olarak kaydedilir

Bu yaklaşım, anahtar sıçramasından kaynaklanabilecek hatalı tetiklemeleri etkili bir şekilde filtreler.

### Debounce Süresini Ayarlama

Eğer tuşlarınızda çift tetikleme veya titreme sorunları yaşıyorsanız, `HID_Macropad_3x3.ino` dosyasında debounce süresini ayarlayabilirsiniz:

```cpp
const unsigned long DEBOUNCE_TIME = 20;  // ms cinsinden (20-50ms arası önerilir)
```

- **20ms**: Çoğu mekanik switch için yeterli (varsayılan)
- **30-40ms**: Daha yüksek kaliteli switch'ler için
- **50ms**: Çok ucuz veya sorunlu switch'ler için

## Diyot Ekleme/Kaldırma Rehberi

### Diyotsuz'dan Diyötlü'ye Geçiş

Eğer diyotsuz kurulum yaptıysanız ve sonradan diyotlu kuruluma geçmek isterseniz:

1. Arduino'nun USB kablosunu çıkarın (güvenlik için)
2. Her switch için:
   - Switch Pin 1 ve GPIO pin arasındaki doğrudan bağlantıyı kesin
   - 1N4148 diyotun katodunu (-) Switch Pin 1'e bağlayın
   - Diyotun anodunu (+) GPIO pinine bağlayın
3. Switch Pin 2 ve GND bağlantısını olduğu gibi bırakın
4. USB kablosunu tekrar takın
5. **Firmware değişikliği GEREKMEZ** - aynı kod her iki kurulumla da çalışır

### Diyötlü'den Diyotsuz'a Geçiş

1. Arduino'nun USB kablosunu çıkarın
2. Her switch için:
   - Diyotları çıkarın
   - Switch Pin 1'i doğrudan GPIO pinine bağlayın
3. Switch Pin 2 ve GND bağlantısını olduğu gibi bırakın
4. USB kablosunu tekrar takın

## Sorun Giderme

| Sorun | Olası Nedenleri | Çözüm |
|-------|-----------------|--------|
| Cihaz algılanmıyor | USB bağlantısı, sürücü | USB kablosunu değiştirin, kartı yeniden başlatın |
| Düğmeler yanıt vermiyor | Pin bağlantısı, yazılım | Pin konfigürasyonunu kontrol edin, seri monitörü açarak hata ayıklayın |
| Düğmeler birden fazla basılı gözüküyor | Debounce süresi | `DEBOUNCE_TIME` değerini artırın (örn. 30-50 ms) |
| Modifiyer tuşlar çalışmıyor | Syntax hatası | `MACRO_BINDINGS` dizisindeki syntax'ı kontrol edin |
| Arduino IDE'de yükleme hatası | Kart/port seçimi | Doğru kart (Leonardo) ve portu seçili olduğundan emin olun |
| Diyot ters bağlandı | Diyot yönü yanlış | Katot (-) switch'e, anot (+) GPIO'ya olmalı - diyot yönünü değiştirin |
| Bazı tuşlar çalışmıyor | Kablo bağlantısı | Her switch'in kablolarını ve sıkılığını kontrol edin |
| D0/D1 pinleri yanıt vermiyor | Seri port çakışması | Seri monitörü kapatın, başka pin kullanın (D2-D8 daha güvenli) |

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
