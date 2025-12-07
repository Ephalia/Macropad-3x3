# Arduino Pro Micro 3x3 HID Macropad - Proje Yapısı

Bu dokümantasyon, Arduino Pro Micro 3x3 HID Macropad projesinin dosya ve dizin yapısını açıklar.

## Genel Proje Yapısı

```
.
├── HID_Macropad_3x3.ino               # Ana Arduino Sketch (Firmware)
├── README.md                          # Türkçe Ana Dokümantasyon
├── PROJECT_STRUCTURE.md               # Bu Dosya
├── .gitignore                         # Git İgnore Dosyası
│
├── docs/                              # Dokümantasyon Klasörü
│   ├── pin_mapping.md                 # Detaylı Pin Eşlemesi (D0-D8)
│   ├── WIRING_GUIDE.md                # Kablolama Rehberi (Diyotsuz + Diyötlü)
│   ├── ARDUINO_IDE_SETUP.md          # Arduino IDE Kurulum Rehberi
│   └── TROUBLESHOOTING.md            # Sorun Giderme Kılavuzu
│
└── examples/                          # Örnek Konfigürasyonlar
    ├── example_productivity.ino       # Verimlilik Makroları
    ├── example_gaming.ino             # Oyun Makroları
    └── example_media.ino              # Medya Kontrol Makroları
```

## Dosya Açıklamaları

### Ana Dosyalar

#### `HID_Macropad_3x3.ino`
- **Amaç**: Ana Arduino firmware sketch dosyası
- **İçerik**:
  - Pin konfigürasyonu (3x3 buton düzeni, D0-D8 pinleri)
  - Makro tuş tanımları (9 tuş kombinasyonu)
  - Debouncing implementasyonu (20ms, ayarlanabilir 20-50ms)
  - USB HID haberleşme kodu
  - Hem diyotsuz hem diyötlü kurulum desteği
- **Kullanım**: Arduino IDE'de açılıp Arduino Pro Micro'ya yüklenir
- **Özelleştirme**: Tuş kombinasyonları bu dosyada `MACRO_BINDINGS` dizisinde değiştirilir
- **Donanım Esnekliği**: Aynı firmware hem diyotsuz hem diyötlü kurulumlarla çalışır

#### `README.md`
- **Amaç**: Proje ana dokümantasyonu (Türkçe)
- **İçerik**:
  - Proje özeti ve özellikler
  - Donanım gereksinimleri
  - Pin eşlemesi tablosu
  - Kurulum ve kullanım talimatları
  - Tuş kombinasyonları özelleştirme rehberi
  - Debouncing açıklaması
  - Sorun giderme başlığı
  - Kaynaklar ve lisans bilgisi
- **Hedef Kitle**: Tüm kullanıcılar, başlangıç noktası

#### `.gitignore`
- **Amaç**: Git tarafından takip edilmeyecek dosyaları belirtir
- **İçerik**:
  - Arduino IDE geçici dosyaları
  - İşletim sistemi spesifik dosyaları
  - IDE ayarları
  - Derlenmiş binaries
- **Önem**: Depo temiz tutmak için gerekli

### Dokümantasyon Dosyaları (`docs/`)

#### `pin_mapping.md`
- **Amaç**: Detaylı pin eşlemesi ve kablolama şemaları
- **İçerik**:
  - Arduino Pro Micro çip referansı
  - Pinout diyagramları (ASCII art, D0-D8 pinleri)
  - Dijital ve analog pin tabloları
  - Makropad pin atama diyagramı
  - Diyotsuz ve diyötlü kablolama şemaları
  - Tuş kombinasyonu referansı
  - Debounce implementasyon detayları (20ms)
  - Sürücü gereksinim bilgisi
  - Kustomizasyon örnekleri
  - Diyot yön kontrolü ve test etme
- **Hedef Kitle**: Donanım kurulumu yapan veya pin konfigürasyonunu değiştirmek isteyen

#### `WIRING_GUIDE.md`
- **Amaç**: Adım adım kablolama rehberi (Diyotsuz ve Diyötlü kurulumlar için)
- **İçerik**:
  - Gerekli malzeme listesi (her iki kurulum için)
  - Diyotsuz kurulum avantaj/dezavantajları ve şema
  - Diyötlü kurulum avantaj/dezavantajları ve şema
  - 1N4148 diyot tanıma ve test etme rehberi
  - Adım adım montaj talimatları (breadboard)
  - Detaylı kablolama tabloları
  - Bağlantı testi prosedürleri
  - Sorun giderme (kablolama spesifik)
  - PCB'ye geçiş ipuçları
  - 3D printable kasa önerileri
- **Hedef Kitle**: İlk kez donanım kurulumu yapan kullanıcılar, başlangıç seviyesi
- **Özel Not**: Bu belge, yeni başlayanlar için en kapsamlı kablolama kaynağıdır

#### `ARDUINO_IDE_SETUP.md`
- **Amaç**: Arduino IDE kurulum ve firmware yükleme adımları
- **İçerik**:
  - Arduino IDE indirme ve kurulumu (Windows/macOS/Linux)
  - Arduino Pro Micro kartı desteğinin eklenmesi
  - Kart ve port seçimi
  - Firmware açma, derleme ve yükleme
  - Seri monitör kullanımı
  - Hata giderme tüyoları
  - İleri kullanıcı özellikleri
- **Hedef Kitle**: Yazılım tarafıyla başlayan ve firmware yüklemek isteyen

#### `TROUBLESHOOTING.md`
- **Amaç**: Yaygın sorunları ve çözümleri kapsamlı şekilde kapsar
- **İçerik**:
  - Genel sorunlar (cihaz algılanmamması, yükleme hataları)
  - Donanım/kablolama sorunları
  - Yazılım/makro sorunları
  - Performans sorunları
  - Arduino IDE sorunları
  - Sistem spesifik sorunlar (Windows/macOS/Linux)
  - İleri hata ayıklama teknikleri
  - Kontrol listeleri
- **Hedef Kitle**: Sorun yaşayan kullanıcılar

### Örnek Dosyaları (`examples/`)

#### `example_productivity.ino`
- **Amaç**: Verimlilik odaklı makro örnekleri
- **İçerik**:
  - Satır 1: Kes/Kopyala/Yapıştır (Ctrl+X/C/V)
  - Satır 2: Kaydet/Farklı Kaydet/Yeni Dosya
  - Satır 3: Geri Al/İleri Al/Tümünü Seç
- **Kullanım**: 
  1. `HID_Macropad_3x3.ino` dosyasında `MACRO_BINDINGS` dizisini bu kodla değiştirin
  2. Derleyin ve yükleyin
  3. Verimlilik makroları şimdi aktif olur
- **Hedef Kitle**: Yazı işleri ve ofis uygulamalarında kullanacak olanlar

#### `example_gaming.ino`
- **Amaç**: Oyun odaklı makro örnekleri
- **İçerik**:
  - Satır 1: Silah seçimi (1-2-3 tuşları)
  - Satır 2: Yetenekler (Q-E-R tuşları)
  - Satır 3: Harita/Sosyal (M-P-Tab tuşları)
- **Kullanım**: Yukarıdakiyle aynı (example_productivity yerine bu kodu kullanın)
- **Hedef Kitle**: Oyun oynayan kullanıcılar
- **Not**: Farklı oyunlar için kustomizasyon örnekleri dosya içinde açıklanmıştır

#### `example_media.ino`
- **Amaç**: Medya kontrol ve web tarayıcı kısayolları
- **İçerik**:
  - Satır 1: Web tarayıcı kontrolleri
  - Satır 2: Ekran görüntüsü ve paylaşım
  - Satır 3: Ses/görüntü ve uygulama yönetimi
- **Kullanım**: Diğer örneklerle aynı
- **Hedef Kitle**: Medya ve web tabanlı çalışma yapan kullanıcılar

## Dosyalar Arası İlişkiler

```
Kullanıcı
    ↓
README.md (Başlangıç)
    ├─→ ARDUINO_IDE_SETUP.md (Yazılım kurulumu)
    │   ├─→ HID_Macropad_3x3.ino (Firmware yükleme)
    │   └─→ Seri Monitör (Test)
    │
    ├─→ docs/pin_mapping.md (Donanım kurulumu)
    │   └─→ Tuş kablolama ve test
    │
    └─→ docs/TROUBLESHOOTING.md (Sorun giderme)

Özelleştirme İçin:
    README.md (Tuş kombinasyonları)
        ↓
    examples/example_*.ino (Referanslar)
        ↓
    HID_Macropad_3x3.ino (Kodu düzenleyin)
        ↓
    ARDUINO_IDE_SETUP.md (Adımlar) → Tekrar yükleyin
```

## Dosya Boyutları ve Kullanım

| Dosya | Boyut | Kullanım Sıklığı |
|-------|-------|-----------------|
| HID_Macropad_3x3.ino | ~3-4 KB | Çok Sık (Firmware) |
| README.md | ~8-10 KB | Sık (Referans) |
| pin_mapping.md | ~10 KB | Orta (Donanım Setup) |
| ARDUINO_IDE_SETUP.md | ~12 KB | Orta (İlk Kurulum) |
| TROUBLESHOOTING.md | ~20 KB | Orta (Sorun Giderme) |
| examples/*.ino | ~2 KB (her biri) | Az (Referans) |

## Yeni Dosya Ekleme

Projeyi genişletmek istiyorsanız, şu yapıyı kullanın:

```
Yeni Feature/Makro
    └─→ examples/example_[feature].ino (Örnek kodu)
    └─→ docs/[feature]_guide.md (Dokümantasyon)
    └─→ README.md (Kısa referans ekleyin)
```

## Versiyon Kontrol (Git)

Proje aşağıdaki dosyaları takip eder:
- `.ino` dosyaları (Kodlar)
- `.md` dosyaları (Dokümantasyon)
- `.gitignore` (Konfigürasyon)

Takip etmemesi gereken:
- `.git/` (Git metadata)
- `build/` (Derlenmiş çıktılar)
- `*.o`, `*.bin`, `*.hex` (Binaries)
- IDE ayarları

## Proje Başlangıç Yolları

### Senaryo 1: Tamamen Yeni Başlayan
1. README.md oku
2. ARDUINO_IDE_SETUP.md adımlarını takip et
3. HID_Macropad_3x3.ino'yu yükle
4. pin_mapping.md'ye göre tuşları kablola
5. Test et

### Senaryo 2: Donanım Kurulu, Yazılım Kurulması Gereken
1. ARDUINO_IDE_SETUP.md adımlarını takip et
2. HID_Macropad_3x3.ino'yu yükle
3. Seri monitörde test et

### Senaryo 3: Makroları Özelleştirmek İsteyen
1. README.md'de "Tuş Kombinasyonlarını Özelleştirme" bölümünü oku
2. examples/ klasöründen bir örnek seç
3. HID_Macropad_3x3.ino dosyasında MACRO_BINDINGS'i güncelle
4. Derle ve yükle

### Senaryo 4: Sorun Yaşayan
1. TROUBLESHOOTING.md'de sorunu ara
2. Önerilen çözümleri dene
3. İleri Hata Ayıklama bölümünü oku

## Bakım ve Güncelleme

Projeyi güncellerken:

1. Değişiklik türünü belirleyin:
   - **Yazılım**: HID_Macropad_3x3.ino
   - **Dokümantasyon**: docs/*.md ve README.md
   - **Yeni Örnekler**: examples/

2. İlgili dosyaları düzenleyin

3. .gitignore'u güncellemeyin (sürece göre)

4. Commit mesajını detaylı yazın:
   ```
   git commit -m "Özellik: [açıklama]"
   git commit -m "Düzeltme: [açıklama]"
   git commit -m "Dokümantasyon: [açıklama]"
   ```

## Sık Sorulan Sorular

**S: Hangi dosyayı ilk okumalıyım?**
C: README.md

**S: Firmware yüklemek için adım adım rehber?**
C: ARDUINO_IDE_SETUP.md

**S: Tuşları nasıl özelleştiririm?**
C: README.md "Tuş Kombinasyonlarını Özelleştirme" ve examples/ klasörü

**S: Hangi dosyayı Arduino IDE'de açmalıyım?**
C: HID_Macropad_3x3.ino

**S: Yeni bir makro seti oluşturabilir miyim?**
C: Evet! examples/ klasöründe örnek vardır

---

**Son Güncelleme**: 2024
**Versiyon**: 1.0
