# Arduino Pro Micro 3x3 Macropad - Pin Eşlemesi Detaylı Belge

## Arduino Pro Micro Çip Referansı

Arduino Pro Micro ATmega32U4 mikrodenetleyicisi taşıdığı için, dijital ve analog pinleri aşağıdaki gibi haritalanır:

### Pinout Diyagramı

```
                    Arduino Pro Micro
                    
        +-------USB-------+
        |  TX   RAW       |
        |  RX   GND       |
        |  GND  RST       |
        |  GND  VCC       |
        |  D2   A3        |
        |  D3   A2        |
        |  D4   A1        |
        |  D5   A0        |
        |  D6   D15       |
        |  D7   D14       |
        |  D8   D16       |
        |  D9   D10       |
        +------RESET------+

TX = D1 (UART)
RX = D0 (UART)
```

### Dijital Pinler ve Fonksiyonları

| Dijital Pin | İşlev | Alternatif | Notlar |
|-------------|-------|-----------|--------|
| D0 | RX | UART0 | Serial haberleşme - **Tuş 1,1 (Ses Azalt)** |
| D1 | TX | UART0 | Serial haberleşme - **Tuş 1,2 (Ses Arttır)** |
| D2 | SDA | I2C | I2C veri hattı - **Tuş 1,3 (Mute)** |
| D3 | SCL | I2C | I2C saat hattı - **Tuş 2,1 (Önceki)** |
| D4 | Makropad | A6 | **Tuş 2,2 (Play/Pause)** |
| D5 | Makropad | - | **Tuş 2,3 (Sonraki)** |
| D6 | Makropad | A7 | **Tuş 3,1 (Alt+F4)** |
| D7 | PWM | OCOA | PWM desteği - **Tuş 3,2 (Win+D)** |
| D8 | PWM | OCOB | PWM desteği - **Tuş 3,3 (Win+L)** |
| D9 | - | OC1A | Boş |
| D10 | - | OC1B | Boş |
| D11 | MOSI | PWM | SPI/PWM |
| D12 | MISO | PCINT | SPI |
| D13 | SCK | LED | SPI/LED |
| D14 | - | A0 | Boş |
| D15 | - | A1 | Boş |
| D16 | - | A2 | Boş |

**⚠️ ÖNEMLİ NOT:** D0 (RX) ve D1 (TX) pinleri seri haberleşme için kullanılır. Eğer seri monitör açıkken bu pinler çalışmayabilir. Normal kullanımda sorun olmaz.

## Makropad Pin Atama Tablosu

### Fiziksel Düzen

```
Tuş 1-1      Tuş 1-2      Tuş 1-3
  (D0)         (D1)         (D2)
   
Tuş 2-1      Tuş 2-2      Tuş 2-3
  (D3)         (D4)         (D5)
   
Tuş 3-1      Tuş 3-2      Tuş 3-3
  (D6)         (D7)         (D8)
```

## Kablolama Şemaları

Bu macropad iki farklı kablolama yöntemi destekler. Her ikisi de aynı firmware ile çalışır.

### SEÇENEK 1: DİYOTSUZ KABLOLAMA (Basit)

```
┌─────────────────────────────────────┐
│   Arduino Pro Micro                 │
├─────────────────────────────────────┤
│   D0 ──────────── SWITCH 1-1 Pin 1  │
│   D1 ──────────── SWITCH 1-2 Pin 1  │
│   D2 ──────────── SWITCH 1-3 Pin 1  │
│   D3 ──────────── SWITCH 2-1 Pin 1  │
│   D4 ──────────── SWITCH 2-2 Pin 1  │
│   D5 ──────────── SWITCH 2-3 Pin 1  │
│   D6 ──────────── SWITCH 3-1 Pin 1  │
│   D7 ──────────── SWITCH 3-2 Pin 1  │
│   D8 ──────────── SWITCH 3-3 Pin 1  │
│                                     │
│   GND ─────┬───── SWITCH 1-1 Pin 2  │
│            ├───── SWITCH 1-2 Pin 2  │
│            ├───── SWITCH 1-3 Pin 2  │
│            ├───── SWITCH 2-1 Pin 2  │
│            ├───── SWITCH 2-2 Pin 2  │
│            ├───── SWITCH 2-3 Pin 2  │
│            ├───── SWITCH 3-1 Pin 2  │
│            ├───── SWITCH 3-2 Pin 2  │
│            └───── SWITCH 3-3 Pin 2  │
└─────────────────────────────────────┘
```

**Tek Buton Bağlantı Örneği (Diyotsuz):**

```
     [SWITCH]
        |  |
        |  └─── GND (siyah kablo)
        └────── GPIO Pin (örn: D0, kırmızı kablo)

Arduino Pro Micro dahili pull-up dirençleri 
etkinleştirir, harici pull-up gerekmez.
```

### SEÇENEK 2: DİYÖTLÜ KABLOLAMA (Profesyonel)

```
┌─────────────────────────────────────────────┐
│   Arduino Pro Micro                         │
├─────────────────────────────────────────────┤
│   D0 ←─[A]─[K]←─ SWITCH 1-1 Pin 1          │
│   D1 ←─[A]─[K]←─ SWITCH 1-2 Pin 1          │
│   D2 ←─[A]─[K]←─ SWITCH 1-3 Pin 1          │
│   D3 ←─[A]─[K]←─ SWITCH 2-1 Pin 1          │
│   D4 ←─[A]─[K]←─ SWITCH 2-2 Pin 1          │
│   D5 ←─[A]─[K]←─ SWITCH 2-3 Pin 1          │
│   D6 ←─[A]─[K]←─ SWITCH 3-1 Pin 1          │
│   D7 ←─[A]─[K]←─ SWITCH 3-2 Pin 1          │
│   D8 ←─[A]─[K]←─ SWITCH 3-3 Pin 1          │
│                                             │
│   GND ─────┬───── SWITCH 1-1 Pin 2          │
│            ├───── SWITCH 1-2 Pin 2          │
│            ├───── SWITCH 1-3 Pin 2          │
│            ├───── SWITCH 2-1 Pin 2          │
│            ├───── SWITCH 2-2 Pin 2          │
│            ├───── SWITCH 2-3 Pin 2          │
│            ├───── SWITCH 3-1 Pin 2          │
│            ├───── SWITCH 3-2 Pin 2          │
│            └───── SWITCH 3-3 Pin 2          │
└─────────────────────────────────────────────┘

NOT: [A] = Anot (+, uzun bacak)
     [K] = Katot (-, kısa bacak, bantlı taraf)
```

**Tek Buton Bağlantı Örneği (Diyötlü):**

```
Arduino       1N4148        Switch
  Pin         Diyot
              
  D0 ←──[+]──[−]←───┐
                    │
                 [Pin 1]
                    │
                 [Pin 2]
                    │
  GND ──────────────┘

Diyot Yönü: Anot (+) → GPIO Pin
           Katot (-) → Switch Pin 1
```

### 1N4148 Diyot Tanıma Rehberi

```
   1N4148 Diyot Görünümü:
   
   ┌─────────┐
   │  ──│    │  ← Bant (Katot tarafı)
   └─────────┘
      ↑    ↑
    Anot  Katot
     (+)   (-)
    Uzun  Kısa
    Bacak Bacak
```

**Diyot Test Etme:**
1. Multimetreyi "diode test" moduna alın
2. Kırmızı prob → Anot (+)
3. Siyah prob → Katot (-)
4. Ekranda ~0.6V görmelisiniz (iletken)
5. Probları ters çevirince ekran "OL" göstermeli (yalıtkan)

## Tuş Kombinasyonu Referansı

### Varsayılan Makrolar

| Satır | Sütun | Pin | Başlangıç Kombinasyonu | Açıklama |
|-------|-------|-----|------------------------|----------|
| 1 | 1 | **D0** | **Volume Down** | Ses Azalt |
| 1 | 2 | **D1** | **Volume Up** | Ses Arttır |
| 1 | 3 | **D2** | **Mute** | Sesi Kapat |
| 2 | 1 | **D3** | **Previous** | Önceki Parça/Video |
| 2 | 2 | **D4** | **Play/Pause** | Oynat/Duraklat |
| 2 | 3 | **D5** | **Next** | Sonraki Parça/Video |
| 3 | 1 | **D6** | `Alt + F4` | Uygulamayı Kapat |
| 3 | 2 | **D7** | `Windows + D` | Masaüstüne Git |
| 3 | 3 | **D8** | `Windows + L` | Bilgisayarı Kilitle |

## Debounce Implementasyon Detayları

### Durum Makinesi

```
          [IDLE]
            |
            | (Durum değişimi algılandı)
            ↓
        [WAITING]  (20ms bekleniyor)
            |
            ├─→ [Durum geri döndü] → [IDLE]
            |
            └─→ [Durum stabildi] → [CONFIRMED]
                                        |
                                        ↓
                                   [İşlem Yap]
                                   (Tuş gönder)
```

### Zaman Çizelgesi

```
t=0ms   : Buton basılır
          → Durum LOW algılanır, lastTime = 0ms

t=5ms   : Sıçrama nedeniyle HIGH olur
          → Durum değişimi algılandı, lastTime = 5ms
          → 20ms beklemeye başla

t=15ms  : Halen HIGH
          → 10ms geçti, yeterli değil

t=25ms  : 20ms geçti ve durum halen HIGH
          → Bounce sona erdi, FALSE press kaydedilir

t=30ms  : Buton gerçekten basılır
          → LOW durumu algılandı, lastTime = 30ms

t=50ms  : 20ms geçti ve durum halen LOW
          → Legitimate press kaydedilir, tuş gönderilir
```

### Debounce Ayarları

```cpp
const unsigned long DEBOUNCE_TIME = 20;  // ms cinsinden (varsayılan)
```

**Önerilen değerler:**
- **20ms**: Çoğu mekanik switch için yeterli (varsayılan)
- **30-40ms**: Daha yüksek kaliteli switch'ler için
- **50ms**: Ucuz veya sorunlu switch'ler için

## Sürücü Gereksinimleri

Arduino Pro Micro ATmega32U4 tabanlı ve yerleşik USB bootloader ile gelir:

### Windows
- Ek sürücü **gerekmez**
- Arduino Pro Micro USB HID cihazı olarak otomatik tanınır
- İlk bağlantıda "Bilinmeyen cihaz" görebilirsiniz, Windows otomatik sürücü bulacaktır

### macOS
- Ek sürücü **gerekmez**
- USB HID cihazı olarak otomatik tanınır

### Linux
- Ek sürücü **gerekmez**
- `/dev/hidraw*` veya `/dev/input/event*` olarak görünür

## Kustomizasyon Örnekleri

### Pin Atamalarını Değiştirme

Eğer farklı pinleri kullanmak istiyorsanız, `HID_Macropad_3x3.ino` dosyasında bu bölümü düzenleyin:

```cpp
const int BUTTON_PINS[3][3] = {
  { 0,  1,  2 },   // Satır 1: D0, D1, D2
  { 3,  4,  5 },   // Satır 2: D3, D4, D5
  { 6,  7,  8 }    // Satır 3: D6, D7, D8
};
```

Örneğin, D9 pinini kullanmak istiyorsanız:

```cpp
const int BUTTON_PINS[3][3] = {
  { 0,  1,  2 },   // Satır 1: D0, D1, D2
  { 3,  4,  5 },   // Satır 2: D3, D4, D5
  { 6,  7,  9 }    // Satır 3: D6, D7, D9 (D8 yerine)
};
```

### Tuş Kombinasyonlarını Değiştirme

Makrolar `MACRO_BINDINGS` dizisinde tanımlanır. İki tür makro kullanabilirsiniz:

**Klavye Kombinasyonu:**
```cpp
// Ctrl+R (Yenile)
{ MACRO_KEYBOARD, KEY_LEFT_CTRL, 'r', 0, 0 }
```

**Medya Kontrol Tuşu:**
```cpp
// Ses Arttır
{ MACRO_CONSUMER, 0, MEDIA_VOLUME_UP, 0, 0 }
```

## Sorun Giderme Pin Sorunları

### "Cihaz algılanmıyor" sorunu

1. **USB kablosunu kontrol edin**: Veri taşıyan bir kablo kullanın (şarj kablosu değil)
2. **Kart seçimini kontrol edin**: Arduino IDE'de "Arduino Leonardo" seçili mi?
3. **Port seçimini kontrol edin**: Doğru COM/ttyACM portunu seçtiniz mi?
4. **Firmware'i yeniden yükleyin**: Reset butonuna basın ve yeniden yükleyin

### "Düğme yanıt vermiyor" sorunu

1. **Kablolamayı kontrol edin**: Switch GND'ye bağlı mı?
2. **Pin numarasını kontrol edin**: BUTTON_PINS dizisinde doğru pin var mı?
3. **Seri monitörde hata ayıklama**: "Tuş tetiklendi" mesajı görüyor musunuz?
4. **Diyot yönünü kontrol edin** (Diyötlü kurulumda): Anot (+) GPIO'ya, Katot (-) switch'e mi?

### "Birden fazla basılı tetikleniyor" sorunu

Debounce süresini artırın:

```cpp
const unsigned long DEBOUNCE_TIME = 30;  // 30ms veya daha fazla
```

### "D0/D1 pinleri çalışmıyor" sorunu

D0 (RX) ve D1 (TX) seri haberleşme için kullanılır. Seri monitör açıkken bu pinler çalışmayabilir:

1. **Çözüm 1**: Seri monitörü kapatın
2. **Çözüm 2**: D0/D1 yerine başka pinleri kullanın (D9, D10 gibi)
3. **Çözüm 3**: Serial.begin() satırını yoruma alın (hata ayıklama yapamayacaksınız)

### "Diyot ters bağlandı" sorunu

Diyot yönü yanlışsa switch çalışmaz. Doğru yön:

```
GPIO Pin ← [Anot(+)] [Katot(-)] ← Switch Pin 1
                ↑          ↑
            Uzun bacak  Kısa bacak
            Bantsız     Bantlı
```

Tüm diyotları kontrol edin ve gerekirse yönünü değiştirin.

## Ek Kaynaklar

- [ATmega32U4 Datasheet](https://ww1.microchip.com/en-US/product/ATMEGA32U4)
- [HID-Project Kütüphanesi (NicoHood)](https://github.com/NicoHood/HID)
- [HID-Project Dokümantasyon](https://github.com/NicoHood/HID/wiki)
- [Arduino Leonardo Pinout](https://www.arduino.cc/en/Hacking/PinMapping32u4)
- [1N4148 Diyot Datasheet](https://www.diodes.com/assets/Datasheets/ds12019.pdf)

---

**Son Güncelleme**: 2024
**Versiyon**: 2.0 (D0-D8 pinler + Diyot desteği)
