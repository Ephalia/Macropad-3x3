/*
 * Örnek: Medya Kontrol Makroları
 * 
 * Bu örnek, gerçek medya kontrolleri (Volume Up/Down, Play/Pause, vb.)
 * ve ekran görüntüsü kısayolları için tuş kombinasyonları tanımlar.
 * 
 * HID_Macropad_3x3.ino dosyasındaki MACRO_BINDINGS 
 * dizisini bu örnekle değiştirerek kullanın.
 * 
 * NOT: Bu örnek HID-Project kütüphanesi ile gerçek medya kontrollerini kullanır.
 */

const MacroKey MACRO_BINDINGS[3][3] = {
  // Satır 1: Ses Kontrolleri (Gerçek HID Medya Tuşları)
  { { MACRO_CONSUMER, 0, MEDIA_VOLUME_DOWN, 0, 0 },   // Ses Azalt
    { MACRO_CONSUMER, 0, MEDIA_VOLUME_UP, 0, 0 },     // Ses Arttır
    { MACRO_CONSUMER, 0, MEDIA_VOLUME_MUTE, 0, 0 } }, // Sesi Kapat
  
  // Satır 2: Medya Oynatıcı Kontrolleri
  { { MACRO_CONSUMER, 0, MEDIA_PREVIOUS, 0, 0 },      // Önceki Parça
    { MACRO_CONSUMER, 0, MEDIA_PLAY_PAUSE, 0, 0 },    // Oynat/Duraklat
    { MACRO_CONSUMER, 0, MEDIA_NEXT, 0, 0 } },        // Sonraki Parça
  
  // Satır 3: Ekran Görüntüsü ve Uygulama Kontrolleri
  { { MACRO_KEYBOARD, 0, KEY_PRINT_SCREEN, 0, 0 },                 // Ekran Görüntüsü
    { MACRO_KEYBOARD, KEY_LEFT_GUI, 'd', 0, 0 },                   // Masaüstüne git
    { MACRO_KEYBOARD, KEY_LEFT_ALT, KEY_F4, 0, 0 } }               // Uygulamayı kapat
};

/*
 * CUSTOMIZATION NOTES / KUSTOMİZASYON NOTLARI:
 * 
 * Diğer Medya Kontrolleri:
 * { { MACRO_CONSUMER, 0, MEDIA_STOP, 0, 0 },           // Durdur
 *   { MACRO_CONSUMER, 0, CONSUMER_CALCULATOR, 0, 0 }, // Hesap Makinesi
 *   { MACRO_CONSUMER, 0, CONSUMER_BROWSER_HOME, 0, 0 } } // Tarayıcı Ana Sayfa
 * 
 * OBS Studio (Yayın Yapma):
 * { { MACRO_KEYBOARD, KEY_LEFT_CTRL | KEY_LEFT_SHIFT, 'r', 0, 0 }, // Kayıt başlat/durdur
 *   { MACRO_KEYBOARD, 0, KEY_F12, 0, 0 },                          // Kaynak ayarları
 *   { MACRO_KEYBOARD, 0, KEY_F11, 0, 0 } }                         // Tam ekran
 * 
 * YouTube / Video İzleme:
 * { { MACRO_KEYBOARD, 0, ' ', 0, 0 },     // Oynat/Duraklat (Boşluk)
 *   { MACRO_KEYBOARD, 0, 'f', 0, 0 },     // Tam ekran
 *   { MACRO_KEYBOARD, 0, 'm', 0, 0 } }    // Sesi kapat
 * 
 * NOT: HID-Project kütüphanesi gerçek Consumer Control medya tuşlarını destekler.
 * Bu tuşlar Windows, macOS ve Linux'ta çalışır ve çoğu medya oynatıcıda desteklenir.
 */
