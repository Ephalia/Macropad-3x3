# Pico HID Macropad Firmware

Raspberry Pi Pico için özel 3x3 (dokuz tuş) macropad firmware'i. USB HID klavye cihazı olarak çalışır. Her fiziksel tuş önceden tanımlanmış bir kısayolu (örn. `Ctrl+C`, `Alt+Tab`, `Win+D`) tetikler ve temiz debouncing ile Windows, macOS ve Linux'ta tak-çalıştır klavye gibi davranır.

## Özellikler

- Resmi Pico SDK ve TinyUSB HID yığını kullanılarak C ile yazılmıştır
- 3×3 ızgara şeklinde düzenlenmiş dokuz bağımsız GPIO girişi
- Yerleşik debouncing (15&nbsp;ms) ile tıkırdamayı önler
- `src/macros.c` dosyası üzerinden yapılandırılabilir kısayol eşlemeleri
- Gerçek tak-çalıştır davranış için USB HID klavye tanımlayıcısı (sürücü gerekmez)
- Donanım pin çıkışları, derleme, yükleme ve özelleştirme adımlarını kapsayan kapsamlı dokümantasyon

## Depo düzeni

```
.
├── CMakeLists.txt
├── include/
│   └── macros.h
├── src/
│   ├── main.c
│   ├── macros.c
│   ├── usb_descriptors.c
│   └── tusb_config.h
├── docs/
│   └── pin_mapping.md
└── README.md
```

## Donanım gereksinimleri

- Raspberry Pi Pico / Pico W (RP2040)
- 9 × anlık basmalı düğme (normalde açık)
- Her düğmeyi GPIO pini ile toprak arasına bağlamak için kablolama (dahili pull-up'lar firmware'de etkinleştirilmiştir)
- USB kablosu (güç, programlama ve HID iletişimi için)

## Pin eşlemesi

Düğmeler satır-satır eşlenir (sol üstten sağ alta):

| Mantıksal konum | GPIO | Varsayılan kısayol |
| --------------- | ---- | ------------------ |
| Satır 1, Sütun 1 | GP2  | `Ctrl + C`       |
| Satır 1, Sütun 2 | GP3  | `Ctrl + V`       |
| Satır 1, Sütun 3 | GP4  | `Ctrl + X`       |
| Satır 2, Sütun 1 | GP5  | `Alt + Tab`      |
| Satır 2, Sütun 2 | GP6  | `Win + D`        |
| Satır 2, Sütun 3 | GP7  | `Win + L`        |
| Satır 3, Sütun 1 | GP8  | `Ctrl + Alt + T` |
| Satır 3, Sütun 2 | GP9  | `Ctrl + Shift + N` |
| Satır 3, Sütun 3 | GP10 | `Ctrl + Z`       |

Diyagramlar ve kablolama notları için [`docs/pin_mapping.md`](docs/pin_mapping.md) dosyasına bakın.

## Firmware'i derleme

1. **Ön koşulları yükleyin**
   - CMake ≥ 3.13
   - ARM GCC araç zinciri (örn. `gcc-arm-none-eabi`)
   - Pico SDK bağımlılıkları (TinyUSB dahil)

2. **Pico SDK'yı edinin**
   - Mevcut bir checkout'a `PICO_SDK_PATH` export edin, **veya** CMake'in otomatik olarak indirmesine izin verin (paketlenmiş `pico_sdk_import.cmake`, ortam değişkeni ayarlanmadığında `FetchContent` kullanır).

3. **Yapılandırın ve derleyin**

   ```bash
   cd /path/to/repo
   cmake -S . -B build
   cmake --build build
   ```

   Başarılı derlemeler `build/` klasörü içinde `.uf2`, `.elf` ve `.bin` dosyaları üretir.

4. **Pico'ya yükleyin**
   - Pico'yu USB ile bağlarken `BOOTSEL` düğmesini basılı tutun.
   - `RPI-RP2` adlı bir yığın depolama aygıtı görünür.
   - `build/pico_hid_macropad.uf2` dosyasını sürücüye kopyalayın. Kart yeniden başlar ve hemen macropad olarak çalışmaya başlar.

## Kısayolları özelleştirme

- GPIO atamalarını veya tuş kombinasyonlarını değiştirmek için `src/macros.c` dosyasını düzenleyin. Her girdi şunları tanımlar:
  - `BUTTON_GPIOS[]`: o düğme için kullanılan fiziksel pin
  - `BUTTON_LABELS[]`: okunabilir isim (isteğe bağlı ancak dokümantasyon için kullanışlı)
  - `MACRO_BINDINGS[]`: değiştirici bitmask artı üç tuş koduna kadar (bkz. `include/macros.h`)
- Desteklenen değiştirici bayrakları ve tuş kodları TinyUSB tarafından tanımlanır (`KEYBOARD_MODIFIER_*`, `HID_KEY_*`).
- Düzenlemeden sonra yeni düzeni uygulamak için yeniden derleyin ve yükleyin.

## Debouncing stratejisi

Her düğme 1&nbsp;ms döngü ile sürekli olarak örneklenir. Bir değişikliğin en az 15&nbsp;ms boyunca kararlı kalması gerekir ki firmware bir basma/bırakma olayını kuyruğa alabilsin. Bu, duyarlı girişi korurken anahtar sıçramasını etkili bir şekilde filtreler.

## Sorun giderme

| Sorun | Çözüm |
| ----- | ----- |
| Cihaz algılanmıyor | Pico'nun doğru şekilde yüklendiğinden ve USB kablosunun veri taşıdığından emin olun. Gerekirse firmware'i yeniden derleyin. |
| Düğmeler birden çok kez tetikleniyor | Toprak bağlantısının doğru olduğunu ve düğmenin yalnızca bir tarafının belirlenen GPIO'ya bağlı olduğunu doğrulayın. Debounce mantığı zaten etkindir; başıboş kablolama gürültüsü en yaygın suçludur. |
| Farklı pinler veya kısayollar gerekli | `src/macros.c` dosyasını güncelleyin ve yeniden derleyin. Düzen değişirse dokümantasyon tablolarını ayarlamayı unutmayın. |

## Lisans

MIT lisansı altında sağlanmıştır (depo geçmişine bakın). Firmware'i kendi macropad projeleriniz için uyarlamaktan çekinmeyin.
