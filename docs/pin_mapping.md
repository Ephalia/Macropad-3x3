# Arduino Pro Micro 3x3 Macropad - Pin Eşlemesi Detaylı Belge

## Arduino Pro Micro Çip Referansı

Arduino Pro Micro ATmega32U4 mikrodenetleyicisi taşıdığı için, dijital ve analog pinleri aşağıdaki gibi haritalanır:

### Pinout Diyagramı

```
                    Arduino Pro Micro
                    
        +-----USB-----+
        |  GND  RAW   |
        |             |
    GND |  D13  D11   | D9
    VCC |  D12  D10   | D8
        |  A0   D16   | D7
        |  A1   D15   | D6
        |  A2   D14   | D5
        |  A3   A4    | D4
        |  GND  A5    | D3
        +----RESET----+
```

### Dijital Pinler ve Fonksiyonları

| Dijital Pin | İşlev | Alternatif | Notlar |
|-------------|-------|-----------|--------|
| D0 | RX | UART0 | Serial haberleşme |
| D1 | TX | UART0 | Serial haberleşme |
| D2 | SDA | I2C | I2C veri hattı |
| D3 | SCL | I2C | I2C saat hattı |
| D4 | Makropad | A6 | **Tuş 1,1** - Ctrl+C |
| D5 | Makropad | A9 | **Tuş 3,2** - Ctrl+Shift+N |
| D6 | Makropad | A7 | **Tuş 1,2** - Ctrl+V |
| D7 | PWM | OCOA | PWM desteği |
| D8 | PWM | OCOB | PWM desteği |
| D9 | Makropad | OC1A | **Tuş 3,1** - Ctrl+Alt+T |
| D10 | Makropad | OC1B | **Tuş 1,3** - Ctrl+X |
| D11 | MOSI | PWM | SPI/PWM |
| D12 | MISO | PCINT | SPI |
| D13 | SCK | LED | SPI/LED |
| D14 | Makropad | A0 | **Tuş 2,2** - Win+D |
| D15 | Makropad | A1 | **Tuş 2,3** - Win+L |
| D16 | Makropad | A2 | **Tuş 2,1** - Alt+Tab |

### Analog Pinler (ADC)

| Pin | Dijital Eş | ATmega32U4 | Kullanım |
|-----|-----------|-----------|---------|
| A0 | D14 | ADC7 | Makropad D14 |
| A1 | D15 | ADC8 | Makropad D15 |
| A2 | D16 | ADC9 | Makropad D16 |
| A3 | D18 | ADC10 | Boş |
| A4 | D19 | ADC11 | Boş |
| A5 | D20 | ADC12 | Boş |
| A6 | D4 | ADC4 | Makropad D4 |
| A7 | D6 | ADC6 | Makropad D6 |

## Makropad Pin Atama Tablosu

### Fiziksel Düzen

```
Butona 1-1    Butona 1-2    Butona 1-3
   (D4)          (D6)          (D10)
   
Butona 2-1    Butona 2-2    Butona 2-3
  (D16)         (D14)         (D15)
   
Butona 3-1    Butona 3-2    Butona 3-3
   (D9)          (D5)          (D3)
```

### Kablolama Şeması

Her buton (switch) aşağıdaki gibi bağlanmalıdır:

```
┌─────────────────────────────┐
│   Arduino Pro Micro        │
├─────────────────────────────┤
│   D4 ──── BUTTON 1-1        │
│   D6 ──── BUTTON 1-2        │
│   D10 ─── BUTTON 1-3        │
│   D16 ─── BUTTON 2-1        │
│   D14 ─── BUTTON 2-2        │
│   D15 ─── BUTTON 2-3        │
│   D9 ──── BUTTON 3-1        │
│   D5 ──── BUTTON 3-2        │
│   D3 ──── BUTTON 3-3        │
│   GND ─── GND (tüm butonlara)│
└─────────────────────────────┘
```

### Buton Bağlantı Örneği

Bir buton fiziksel şekilde şu şekilde bağlanır:

```
         [BUTTON SWITCH]
              |  |
              |  └─── GND (toprak, siyah kablo)
              └────── GPIO Pin (yeşil kablo)
                      (Örn: D4, D6, D10, vb.)

Arduino Pro Micro aynı zamanda dahili pull-up 
dirençleri etkinleştirir, bu nedenle harici 
pull-up direnci gerekmez.
```

## Tuş Kombinasyonu Referansı

### Varsayılan Makrolar

| Satır | Sütun | Pin | Başlangıç Kombinasyonu | Açıklama |
|-------|-------|-----|------------------------|----------|
| 1 | 1 | D4 | `Ctrl + C` | Kopyala |
| 1 | 2 | D6 | `Ctrl + V` | Yapıştır |
| 1 | 3 | D10 | `Ctrl + X` | Kes |
| 2 | 1 | D16 | `Alt + Tab` | Pencere geçişi |
| 2 | 2 | D14 | `Windows + D` | Masaüstünü göster |
| 2 | 3 | D15 | `Windows + L` | Kilitle |
| 3 | 1 | D9 | `Ctrl + Alt + T` | Terminal (Linux) |
| 3 | 2 | D5 | `Ctrl + Shift + N` | Yeni dosya (Dosya yöneticisi) |
| 3 | 3 | D3 | `Ctrl + Z` | Geri Al |

## Debounce Implementasyon Detayları

### Durum Makinesi

```
          [IDLE]
            |
            | (Durum değişimi algılandı)
            ↓
        [WAITING]  (15ms bekleniyor)
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
          → 15ms beklemeye başla

t=10ms  : Halen HIGH
          → 5ms geçti, yeterli değil

t=20ms  : 15ms geçti ve durum halen HIGH
          → Bounce sona erdi, FALSE press kaydedilir

t=25ms  : Buton gerçekten basılır
          → LOW durumu algılandı, lastTime = 25ms

t=40ms  : 15ms geçti ve durum halen LOW
          → Legitimate press kaydedilir, tuş gönderilir
```

## Sürücü Gereksinimler

Arduino Pro Micro ATmega32U4 tabanlı ve yerleşik USB bootloader ile gelir:

### Windows
- Ek sürücü **gerekmez**
- Arduino Pro Micro USB HID cihazı olarak otomatik tanınır
- Ilk bağlantıda "Bilinmeyen cihaz" görebilirsiniz, Windows otomatik sürücü bulacaktır

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
  { 4,  6, 10 },   // Satır 1
  { 16, 14, 15 },  // Satır 2
  { 9, 5, 3 }      // Satır 3
};
```

Örneğin, D7 pinini kullanmak istiyorsanız:

```cpp
const int BUTTON_PINS[3][3] = {
  { 4,  6, 7 },    // Satır 1: D4, D6, D7 (D10 yerine)
  { 16, 14, 15 },  // Satır 2
  { 9, 5, 3 }      // Satır 3
};
```

### Tuş Kombinasyonlarını Değiştirme

Makrolar `MACRO_BINDINGS` dizisinde tanımlanır. Örnek olarak, ilk buton yerine "Refresh" yapmak istiyorsanız:

```cpp
// Önceki:
{ { KEY_LEFT_CTRL, 'c', 0, 0 },          // Ctrl+C

// Sonrası:
{ { KEY_LEFT_CTRL, 'r', 0, 0 },          // Ctrl+R (Refresh)
```

## Sorun Giderme Pin Sorunları

### "Cihaz algılanmıyor" sorunu

1. **USB kablosunu kontrol edin**: Veri taşıyan bir kablo kullanın (şarj kablosu değil)
2. **Kart seçimini kontrol edin**: Arduino IDE'de "Arduino Leonardo" seçili mi?
3. **Port seçimini kontrol edin**: Doğru COM/ttyACM portunu seçtiniz mi?
4. **Firmware'i yeniden yükleyin**: BOOTSEL moduna girin ve yeniden yükleyin

### "Düğme yanıt vermiyor" sorunu

1. **Kablolamayı kontrol edin**: Buton GND'ye bağlı mı?
2. **Pin numarasını kontrol edin**: BUTTON_PINS dizisinde doğru pin var mı?
3. **Seri monitörde hata ayıklama**: "Tuş tetiklendi" mesajı görüyor musunuz?

### "Birden fazla basılı tetikleniyor" sorunu

Debounce süresini artırın:

```cpp
const unsigned long DEBOUNCE_TIME = 20;  // 20ms olarak artırın
```

## Ek Kaynaklar

- [ATmega32U4 Datasheet](https://ww1.microchip.com/en-US/product/ATMEGA32U4)
- [Arduino HID Kütüphanesi](https://github.com/arduino-libraries/HID)
- [Arduino Leonardo Pinout](https://www.arduino.cc/en/Hacking/PinMapping32u4)

---

**Son Güncelleme**: 2024
**Versiyon**: 1.0
