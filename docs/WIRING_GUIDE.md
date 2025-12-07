# Arduino Pro Micro 3x3 Macropad - Kablolama Rehberi

Bu belge, Arduino Pro Micro 3x3 Macropad'inizin fiziksel kurulumu için detaylı adım adım talimatlar içerir.

## İçindekiler

1. [Gerekli Malzemeler](#gerekli-malzemeler)
2. [Diyotsuz Kurulum (Basit)](#diyotsuz-kurulum-basit)
3. [Diyötlü Kurulum (Profesyonel)](#diyötlü-kurulum-profesyonel)
4. [Adım Adım Montaj](#adım-adım-montaj)
5. [Bağlantı Testi](#bağlantı-testi)
6. [Sorun Giderme](#sorun-giderme)

---

## Gerekli Malzemeler

### Her İki Kurulum İçin Ortak

| Malzeme | Miktar | Açıklama |
|---------|--------|----------|
| Arduino Pro Micro | 1 | ATmega32U4 tabanlı |
| Mekanik Switch | 9 | Cherry MX, Gateron, Kailh vb. |
| Breadboard | 1 | 830 delik veya daha büyük |
| Jumper Kablolar (M-M) | 10-15 | 10-15cm uzunluk |
| Jumper Kablolar (M-F) | 5-10 | Opsiyonel |
| USB Kablosu | 1 | Micro-USB veya USB-C |

### Sadece Diyötlü Kurulum İçin Ek

| Malzeme | Miktar | Açıklama |
|---------|--------|----------|
| 1N4148 Diyot | 9 | Kısa devre koruması için |

---

## Diyotsuz Kurulum (Basit)

### Avantajlar
- ✅ Daha basit ve hızlı kurulum
- ✅ Daha az malzeme ve maliyet
- ✅ Yeni başlayanlar için ideal
- ✅ 3x3 gibi küçük kurulumlar için yeterli

### Dezavantajlar
- ⚠️ Kısa devre riskine karşı biraz daha hassas
- ⚠️ Gelecekte matrix keyboard'a geçişte yeniden kablolama gerekir

### Basit Şema

```
Switch Pin 1 ──────> GPIO Pin (D0-D8)
Switch Pin 2 ──────> GND
```

### Detaylı Kablolama Tablosu

| Tuş | Satır | Sütun | GPIO Pin | Switch Pin 1 → | Switch Pin 2 → | Fonksiyon |
|-----|-------|-------|----------|----------------|----------------|-----------|
| 1 | 1 | 1 | D0 | D0 | GND | Volume Down |
| 2 | 1 | 2 | D1 | D1 | GND | Volume Up |
| 3 | 1 | 3 | D2 | D2 | GND | Mute |
| 4 | 2 | 1 | D3 | D3 | GND | Previous |
| 5 | 2 | 2 | D4 | D4 | GND | Play/Pause |
| 6 | 2 | 3 | D5 | D5 | GND | Next |
| 7 | 3 | 1 | D6 | D6 | GND | Alt+F4 |
| 8 | 3 | 2 | D7 | D7 | GND | Win+D |
| 9 | 3 | 3 | D8 | D8 | GND | Win+L |

### Görsel Kablolama (Tüm Tuşlar)

```
                    Arduino Pro Micro
                    
        +-------------------------------------------+
        |  TX(D1)  RAW                              |
        |  RX(D0)  GND ─────────┐                   |
        |  GND     RST          │                   |
        |  GND     VCC          │                   |
        |  D2      A3           │                   |
        |  D3      A2           │                   |
        |  D4      A1           │                   |
        |  D5      A0           │                   |
        |  D6      D15          │                   |
        |  D7      D14          │                   |
        |  D8      D16          │                   |
        |  D9      D10          │                   |
        +-------------------------------------------+
           │  │  │  │  │  │  │  │  │               │
           │  │  │  │  │  │  │  │  │               │
           │  │  │  │  │  │  │  │  │               │
         ┌─┴──┴──┴──┴──┴──┴──┴──┴──┴───┐           │
         │ [SW1][SW2][SW3]              │           │
         │ [SW4][SW5][SW6]              │◄──────────┤ (Tüm switchlerin
         │ [SW7][SW8][SW9]              │           │  Pin 2'leri GND'ye)
         └──────────────────────────────┘           │
                                                    │
                  GND Rail ◄────────────────────────┘
```

---

## Diyötlü Kurulum (Profesyonel)

### Avantajlar
- ✅ Kısa devre koruması (ghosting tamamen önlenir)
- ✅ Daha güvenli ve profesyonel
- ✅ Matrix keyboard'a kolay geçiş
- ✅ Büyük projelere hazırlık

### Dezavantajlar
- ⚠️ Biraz daha karmaşık kurulum
- ⚠️ Ek maliyet (9 adet 1N4148 diyot ~5-10 TL)

### Basit Şema

```
Switch Pin 1 ──> 1N4148 Katodu [-]
Diyot Anodu [+] ──> GPIO Pin (D0-D8)
Switch Pin 2 ──> GND
```

### Detaylı Kablolama Tablosu

| Tuş | GPIO | Switch Pin 1 → | Diyot Katodu → | Diyot Anodu → | Switch Pin 2 → | Fonksiyon |
|-----|------|----------------|----------------|---------------|----------------|-----------|
| 1 | D0 | Diyot K | Switch P1 | D0 | GND | Volume Down |
| 2 | D1 | Diyot K | Switch P1 | D1 | GND | Volume Up |
| 3 | D2 | Diyot K | Switch P1 | D2 | GND | Mute |
| 4 | D3 | Diyot K | Switch P1 | D3 | GND | Previous |
| 5 | D4 | Diyot K | Switch P1 | D4 | GND | Play/Pause |
| 6 | D5 | Diyot K | Switch P1 | D5 | GND | Next |
| 7 | D6 | Diyot K | Switch P1 | D6 | GND | Alt+F4 |
| 8 | D7 | Diyot K | Switch P1 | D7 | GND | Win+D |
| 9 | D8 | Diyot K | Switch P1 | D8 | GND | Win+L |

### Diyot Yön Kontrolü

**ÇOK ÖNEMLİ:** Diyot yönü yanlış olursa switch çalışmaz!

```
Doğru Yön:

   GPIO Pin ←──[Anot]──[Katot]←── Switch Pin 1
                 (+)      (-)
              Uzun bacak Kısa bacak
               Bantsız    Bantlı


1N4148 Diyot Fiziksel Görünümü:

    ┌─────────────┐
    │      ║      │  ← Siyah bant (Katot tarafı)
    └─────────────┘
         ↑     ↑
       Anot  Katot
        (+)   (-)
      Uzun   Kısa
      bacak  bacak
```

### Diyot Test Etme (Multimetre ile)

1. Multimetreyi "diode test" (⏵|) moduna alın
2. Kırmızı prob (+) → Anot (uzun bacak)
3. Siyah prob (-) → Katot (kısa bacak, bantlı)
4. **Sonuç:** Ekranda ~0.6V veya ~600mV görmelisiniz
5. Probları ters çevirin
6. **Sonuç:** Ekranda "OL" (Open Loop) görmelisiniz

**Eğer her iki yönde de OL görüyorsanız:** Diyot bozuk
**Eğer her iki yönde de 0.6V görüyorsanız:** Diyot kısa devre yapmış

---

## Adım Adım Montaj

### 1. Hazırlık

1. ✓ Tüm malzemeleri toplayın
2. ✓ Breadboard'u temiz bir yüzeye yerleştirin
3. ✓ Arduino Pro Micro'yu breadboard'un ortasına yerleştirin
4. ✓ GND pinlerinden birini breadboard'un GND rail'ine bağlayın

### 2. Diyotsuz Kurulum Adımları

#### Adım 2.1: İlk Switch'i Bağlayın (Test)

```
1. SW1'i breadboard'a yerleştirin
2. SW1 Pin 1'i jumper ile D0'a bağlayın
3. SW1 Pin 2'yi GND rail'ine bağlayın
4. Arduino'yu USB ile bilgisayara bağlayın
5. Firmware'i yükleyin (eğer henüz yüklemediyseniz)
6. SW1'e basın - ses azaltmalı
7. Çalışıyorsa diğer switch'lere geçin
```

#### Adım 2.2: Tüm Switch'leri Bağlayın

Her switch için tekrarlayın:
- Pin 1 → İlgili GPIO pinine (D0-D8)
- Pin 2 → GND rail'ine

**İpucu:** Renk kodlu kablolar kullanın:
- Kırmızı: GPIO pinleri için
- Siyah: GND için

### 3. Diyötlü Kurulum Adımları

#### Adım 3.1: Diyotları Hazırlayın

1. 9 adet 1N4148 diyot alın
2. Her diyotta bantlı tarafı (katot) işaretleyin
3. Gerekirse diyot bacaklarını kısaltın (isteğe bağlı)

#### Adım 3.2: İlk Switch + Diyot Bağlayın (Test)

```
1. SW1'i breadboard'a yerleştirin
2. Bir diyot alın, katodu (-) tanımlayın
3. Diyot Katodu (-) → SW1 Pin 1'e bağlayın
4. Diyot Anodu (+) → D0'a bağlayın
5. SW1 Pin 2 → GND rail'ine bağlayın
6. Arduino'yu USB ile bilgisayara bağlayın
7. Firmware'i yükleyin
8. SW1'e basın - ses azaltmalı
9. Çalışıyorsa diğer switch'lere geçin
```

#### Adım 3.3: Tüm Switch + Diyot Kombinasyonlarını Bağlayın

Her switch için tekrarlayın:
- Switch Pin 1 → Diyot Katodu (-)
- Diyot Anodu (+) → İlgili GPIO pinine (D0-D8)
- Switch Pin 2 → GND rail'ine

**İpucu:** Her diyotu bağladıktan sonra multimetre ile test edin.

---

## Bağlantı Testi

### Test 1: Görsel Kontrol

✓ Tüm kablolar sıkı mı?  
✓ Hiçbir kablo gevşek değil mi?  
✓ Diyotlar doğru yönde mi? (Diyötlü kurulumda)  
✓ GND rail'i Arduino GND'ye bağlı mı?  
✓ USB kablosu bilgisayara bağlı mı?

### Test 2: Multimetre ile Test

**Her GPIO pin için:**
1. Switch'e basmadan ölçüm yapın
2. Multimetre → "Voltage DC" modu
3. Kırmızı prob → GPIO pin
4. Siyah prob → GND
5. **Beklenen:** ~5V (pull-up aktif)
6. Switch'e basın
7. **Beklenen:** ~0V (GND'ye bağlı)

### Test 3: Seri Monitör ile Test

1. Arduino IDE'yi açın
2. **Araçlar → Seri Monitör** (Ctrl+Shift+M)
3. Baud rate: 9600
4. Her switch'e basın
5. **Beklenen çıktı:**
```
Arduino Pro Micro 3x3 Macropad başlatılıyor...
Macropad başarıyla başlatıldı!
Tuş tetiklendi: Satır 1, Sütun 1
Tuş tetiklendi: Satır 1, Sütun 2
...
```

### Test 4: Fonksiyonel Test

| Tuş | GPIO | Fonksiyon | Test Yöntemi |
|-----|------|-----------|--------------|
| 1 | D0 | Volume Down | Ses azalmalı |
| 2 | D1 | Volume Up | Ses artmalı |
| 3 | D2 | Mute | Ses kapanmalı |
| 4 | D3 | Previous | YouTube'da önceki video |
| 5 | D4 | Play/Pause | YouTube durmalı/başlamalı |
| 6 | D5 | Next | YouTube'da sonraki video |
| 7 | D6 | Alt+F4 | Aktif pencere kapanmalı |
| 8 | D7 | Win+D | Masaüstü gösterilmeli |
| 9 | D8 | Win+L | Bilgisayar kilitlenmeli |

---

## Sorun Giderme

### Sorun: Hiçbir switch yanıt vermiyor

**Olası Nedenler:**
- Arduino'ya güç gelmiyor
- Firmware yüklenmemiş
- GND rail bağlı değil

**Çözümler:**
1. USB kablosunu kontrol edin
2. Arduino IDE'de "Araçlar → Port" kontrol edin
3. Firmware'i yeniden yükleyin
4. GND rail bağlantısını kontrol edin

### Sorun: Bazı switch'ler çalışmıyor

**Olası Nedenler:**
- Kablo gevşek
- Diyot ters bağlı (diyötlü kurulum)
- Hatalı switch

**Çözümler:**
1. İlgili switch'in kablolarını kontrol edin
2. Multimetre ile GPIO pini test edin
3. Diyot yönünü kontrol edin (diyötlü kurulum)
4. Switch'i başka bir switch ile değiştirip test edin

### Sorun: Switch'e birden fazla kez basılmış gibi oluyor

**Olası Nedenler:**
- Debounce süresi yetersiz
- Kötü kalite switch
- Kablo teması zayıf

**Çözümler:**
1. `DEBOUNCE_TIME` değerini artırın (30-50ms)
2. Kablo bağlantılarını sıkılaştırın
3. Daha kaliteli switch kullanın

### Sorun: D0 veya D1 pinleri çalışmıyor

**Olası Neden:**
- Seri monitör açık (D0/D1 UART pinleri)

**Çözümler:**
1. Seri monitörü kapatın
2. Serial.begin(9600) satırını yoruma alın
3. D0/D1 yerine D9/D10 kullanın

### Sorun: Diyot çalışmıyor (Diyötlü kurulum)

**Olası Nedenler:**
- Diyot ters bağlı
- Diyot bozuk
- Kötü bağlantı

**Çözümler:**
1. Diyot yönünü kontrol edin (Anot → GPIO, Katot → Switch)
2. Multimetre ile diyot test edin
3. Diyotu değiştirin
4. Bağlantıları yeniden yapın

---

## Ek İpuçları

### Breadboard Düzeni

```
         [SW1] [SW2] [SW3]
         [SW4] [SW5] [SW6]
         [SW7] [SW8] [SW9]
         
         [ Arduino Pro Micro ]
         
         [GND Rail]
```

### Kablo Organizasyonu

1. **Kısa kablolar kullanın**: Daha temiz görünüm
2. **Renk kodlama**: Kırmızı (GPIO), Siyah (GND)
3. **Etiketleme**: Karışıklığı önlemek için kabloları etiketleyin
4. **Kablo kanalları**: Breadboard üzerinde kabloları düzenli tutun

### PCB'ye Geçiş

Breadboard ile test ettikten sonra kalıcı PCB yapabilirsiniz:

1. **Protoboard kullanın**: Solderlandırmalı breadboard
2. **KiCad ile tasarım**: Profesyonel PCB tasarımı
3. **PCB üretimi**: JLCPCB, PCBWay gibi servisler

### 3D Printable Kasa

Macropad'iniz için 3D baskı kasa yapabilirsiniz:
- Thingiverse'de "3x3 macropad case" arayın
- Fusion 360 ile kendi kasanızı tasarlayın
- 9 switch için Cherry MX montaj delikleri

---

## Kaynaklar

- [Arduino Pro Micro Pinout](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide)
- [Cherry MX Switch Datasheet](https://www.cherrymx.de/en/dev.html)
- [1N4148 Diyot Datasheet](https://www.diodes.com/assets/Datasheets/ds12019.pdf)
- [HID-Project Kütüphanesi](https://github.com/NicoHood/HID)

---

**Son Güncelleme**: 2024  
**Versiyon**: 1.0

**Yazar Notları:**  
Bu kablolama rehberi, yeni başlayanlar ve deneyimli kullanıcılar için hazırlanmıştır. Adım adım takip ederek başarılı bir şekilde macropad'inizi kurabilirsiniz. Sorularınız için GitHub Issues kullanabilirsiniz.
