# Arduino IDE Kurulum Rehberi

Bu dokümantasyon, Arduino Pro Micro 3x3 Macropad firmware'ini Arduino IDE'de derleme ve yükleme işlemini adım adım anlatır.

## Gereksinimler

- **Windows, macOS veya Linux** işletim sistemi
- **Arduino IDE 1.8.x veya 2.x versiyonu**
- **USB to Micro USB kablosu** (Arduino Pro Micro ile uyumlu)
- **Internet bağlantısı** (Arduino paketleri indirmek için)

## Adım 1: Arduino IDE İndirme ve Kurulumu

### Windows için:

1. https://www.arduino.cc/en/software adresine gidin
2. "Arduino IDE" kısmından Windows installer'ı indirin
3. İndirilen `ArduinoSetup.exe` dosyasını çalıştırın
4. Kurulum sihirbazını takip edin (varsayılan seçenekleri kullanabilirsiniz)
5. Kurulum tamamlandıktan sonra Arduino IDE'yi açın

### macOS için:

1. https://www.arduino.cc/en/software adresine gidin
2. macOS versiyonunuza uygun `.dmg` dosyasını indirin
3. `Arduino.dmg` dosyasını açın
4. Arduino ikonu "Applications" klasörüne sürükleyin
5. Uygulamalar klasöründen Arduino IDE'yi açın

### Linux (Ubuntu/Debian) için:

```bash
# Terminal'de aşağıdaki komutları çalıştırın:
sudo apt-get update
sudo apt-get install arduino arduino-core

# Veya Arduino IDE 2.x için:
cd ~/Downloads
wget https://downloads.arduino.cc/arduino-ide/arduino-ide_2.0.0_Linux_64bit.AppImage
chmod +x arduino-ide_2.0.0_Linux_64bit.AppImage
./arduino-ide_2.0.0_Linux_64bit.AppImage
```

## Adım 2: HID-Project Kütüphanesinin Kurulumu

**ÖNEMLİ**: Bu firmware medya kontrolleri (ses ayarları, play/pause, vb.) için HID-Project kütüphanesine ihtiyaç duyar.

1. Arduino IDE'yi açın
2. **Taslak → Kütüphane Ekle → Kütüphaneleri Yönet** menüsüne gidin
3. Arama kutusuna "HID-Project" yazın
4. **HID-Project by NicoHood** kütüphanesini bulun
5. En son versiyonu seçin (önerilen: v2.8.4 veya üzeri)
6. **Yükle** butonuna tıklayın
7. Yükleme tamamlanana kadar bekleyin

## Adım 3: Arduino Pro Micro Kartı Desteğinin Eklenmesi

### Method 1: Arduino Leonardo Kartını Kullanma (En Kolay)

Arduino Pro Micro ve Leonardo aynı ATmega32U4 çipini kullandığı için, Arduino Leonardo desteğini yükleyebilirsiniz:

1. Arduino IDE'yi açın
2. **Araçlar → Kart → Kart Yöneticisi** menüsüne gidin
3. Arama kutusuna "Leonardo" yazın
4. "Arduino AVR Boards" paketini bulun ve "Yükle" butonuna tıklayın

### Method 2: Adafruit Paketini Kullanma (Tercih Edilen)

Arduino Pro Micro'nın özel desteğini Adafruit paketinden yükleyin:

1. Arduino IDE'yi açın
2. **Dosya → Tercihler** menüsüne gidin (Windows/Linux) veya **Arduino → Tercihleri** (macOS)
3. "Ek Kartlar Yöneticisi URL'leri" alanını bulun
4. Aşağıdaki URL'yi ekleyin:
   ```
   https://adafruit.github.io/arduino-board-support/package_adafruit_index.json
   ```
5. **Tamam** butonuna tıklayın
6. **Araçlar → Kart → Kart Yöneticisi** menüsüne gidin
7. Arama kutusuna "pro micro" yazın
8. "Adafruit AVR Boards" paketini bulun ve "Yükle" butonuna tıklayın

## Adım 4: Kart ve Port Seçimi

1. Arduino IDE'yi açın
2. **Araçlar → Kart** menüsünde:
   - Eğer Leonardo paketi yüklediyseniz: **Arduino Leonardo** seçin
   - Eğer Adafruit paketi yüklediyseniz: **Adafruit Pro Micro** seçin
3. **Araçlar → Processor** menüsünde:
   - **ATmega32U4 (5V, 16MHz)** seçin
4. **Araçlar → Port** menüsünde:
   - Arduino Pro Micro'nun bağlı olduğu portu seçin
   - Windows: COM3, COM4, vb.
   - macOS: /dev/cu.usbmodem*, /dev/cu.usbserial-*
   - Linux: /dev/ttyACM0, /dev/ttyUSB0, vb.

**Not**: Port görüntülenmiyorsa, USB kablosunun düzgün takılı olduğundan emin olun ve Arduino IDE'yi yeniden başlatın.

## Adım 5: Firmware Dosyasını Açma

1. `HID_Macropad_3x3.ino` dosyasını Arduino IDE'de açın:
   - **Dosya → Aç** menüsü veya
   - Arduino IDE'ye dosya sürükleyin
2. Kod düzenleyicide Ana IDE penceresinde görünür

## Adım 6: Derleme Kontrolü (Verify)

Kodun syntaksının doğru olduğunu kontrol etmek için:

1. **Taslak → Doğrula/Derle** menüsüne tıklayın (veya `Ctrl+R` / `Cmd+R`)
2. Alt bölümdeki "Çıkış" penceresinde derlemesi başlar
3. İşlem tamamlandığında şu mesajı görürseniz başarılıdır:
   ```
   Derlemesi başarılı oldu.
   (xxxx bayt bellek kullanılıyor)
   ```

**Hata oluşursa**: Çıkış penceresindeki hata mesajını okuyun. Genellikle syntax hataları içerir.

## Adım 7: Arduino Pro Micro'ya Yükleme

### Windows ve macOS:

1. Arduino Pro Micro'yu USB kablosu ile bilgisayara bağlayın
2. Arduino IDE'de portu seçili olduğundan emin olun
3. **Taslak → Yükle** menüsüne tıklayın (veya `Ctrl+U` / `Cmd+U`)
4. Yükleme başlayacak. Aşağıdaki mesajı göreceksiniz:
   ```
   Cihaz Yanıtlı
   Yükleme başladı
   100% Tamamlandı
   ```
5. Yükleme tamamlandıktan sonra Arduino Pro Micro otomatik olarak macropad'i olmaya başlar

### Linux (Ek Adım):

Linux'ta yükleme öncesinde permissions ayarlamanız gerekebilir:

```bash
# Aşağıdaki komutu terminalden çalıştırın:
sudo usermod -a -G dialout $USER

# Sonrasında bilgisayarı yeniden başlatın veya:
newgrp dialout
```

## Sorun Giderme

### Sorun: "Cihaz algılanmıyor"

**Çözüm:**
1. USB kablosunu kontrol edin (veri kablosu olmalı, sadece şarj değil)
2. USB portunu değiştirmeyi deneyin
3. Arduino IDE'yi kapatıp yeniden açın
4. Arduino Pro Micro'yu yeniden başlatın (power kes/tak)

### Sorun: "Port seçenekleri görünmüyor"

**Çözüm:**
1. Arduino Pro Micro'nun USB kablosu ile bağlı olduğundan emin olun
2. **Araçlar → Port** menüsü seçili kapalı listeleyin
3. Doğru kartın seçili olduğundan emin olun
4. Windows'ta Cihaz Yöneticisi'nde Arduino Pro Micro'nun görünüp görmediğini kontrol edin
5. Linux'ta `ls /dev/ttyACM*` veya `ls /dev/ttyUSB*` komutunu çalıştırın

### Sorun: "Yükleme başarısız oldu" hatası

**Çözüm:**
1. Arduino IDE ve Arduino Pro Micro'yu çıkartıp yeniden bağlayın
2. **Bootloader moduna gir**: Arduino Pro Micro üzerindeki RESET düğmesine iki kez hızlı tıklayın
3. LED'ler hızlı yanıp sönmeye başlıyorsa, bootloader moduna girmiş demektir
4. Tekrar yükleme işlemini deneyiniz
5. Doğru **Kart** ve **Port** seçeneklerini doğrulayın

### Sorun: Firmware yüklendi ama macropad çalışmıyor

**Çözüm:**
1. Tuşların fiziksel olarak doğru pinlere bağlı olup olmadığını kontrol edin
2. **Araçlar → Seri Monitörü** açın (hız: 9600 baud)
3. Seri monitörde `Macropad başarıyla başlatıldı!` mesajını görmüş müsünüz?
4. Tuşa basıp `Tuş kombinasyonu tetiklendi` mesajını görüyor musunuz?
5. Görmüyorsanız pin konfigürasyonunu kontrol edin

## Seri Monitör ile Hata Ayıklama

Macropad'in çalışıp çalışmadığını test etmek için seri monitörü kullanabilirsiniz:

1. Arduino IDE'de **Araçlar → Seri Monitörü** aç
2. Hız **9600 baud** olarak ayarla
3. Çıkış penceresinde başlangıç mesajlarını görmelisiniz:
   ```
   Arduino Pro Micro 3x3 Macropad başlatılıyor...
   Macropad başarıyla başlatıldı!
   ```
4. Bir tuşa basıp `Tuş kombinasyonu tetiklendi: Satır 1, Sütun 1` mesajını gözlemleyin

## Firmware Güncelleme

Firmware'i güncellemek (örneğin makroları değiştirmek) için:

1. `.ino` dosyasını düzenleyin
2. **Taslak → Doğrula/Derle** ile kontrol edin
3. Arduino Pro Micro'yu bağlayın
4. **Taslak → Yükle** ile yeni firmware'i yükleyin

Yükleme işlemi tamamlandığında macropad yeni ayarlarla çalışmaya başlar.

## İleri Kullanıcı İpuçları

### Arduino IDE 2.x Yeni Özellikler

Arduino IDE 2.x'de şu yetenekler vardır:
- Geliştirilmiş kod tamamlama (autocompletion)
- Kod hata vurgulama (syntax highlighting)
- Hata ve uyarıları inline gösterme
- Cloud sync seçeneği

### Harici Kütüphanelerin Eklenmesi

Eğer başka HID kütüphaneleri eklemek istiyorsanız:

1. **Taslak → Kütüphane Ekle** menüsüne gidin
2. Kütüphane adını arayın
3. "Yükle" butonuna tıklayın

### Serial Veri İletişimi

Hata ayıklamada seri haberleşmeyi kullanmak için:

```cpp
// Başlatma
Serial.begin(9600);

// Yazdırma
Serial.println("Mesaj");
Serial.print(variable);
```

## Ek Kaynaklar

- **Arduino Resmi Sitesi**: https://www.arduino.cc
- **Arduino Pro Micro Dokümantasyon**: https://www.arduino.cc/en/Main/ArduinoBoardProMicro
- **Leonardo Pinout Referansı**: https://www.arduino.cc/en/Hacking/PinMapping32u4
- **HID-Project Kütüphanesi**: https://github.com/NicoHood/HID
- **HID-Project Dokümantasyon**: https://github.com/NicoHood/HID/wiki

---

**Yazar**: Arduino Pro Micro Macropad Geliştirme Takımı
**Son Güncelleme**: 2024
