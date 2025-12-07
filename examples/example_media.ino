/*
 * Örnek: Medya Kontrol Makroları
 * 
 * Bu örnek, medya oynatıcı kontrolü ve 
 * ses ayarları için tuş kombinasyonları tanımlar.
 * 
 * HID_Macropad_3x3.ino dosyasındaki MACRO_BINDINGS 
 * dizisini bu örnekle değiştirerek kullanın.
 * 
 * NOT: Medya kontrol tuşları (Play, Volume Up, vb.) 
 * Arduino tarafından doğrudan desteklenmez. Bunun yerine,
 * uygulama spesifik kısayollar veya konsol komutları kullanıyoruz.
 */

const MacroKey MACRO_BINDINGS[3][3] = {
  // Satır 1: Web Tarayıcı Kontrolleri
  { { KEY_LEFT_CTRL | KEY_LEFT_SHIFT, KEY_DELETE, 0, 0 }, // Tarayıcı geçmişi sil
    { KEY_LEFT_CTRL, KEY_PAGE_UP, 0, 0 },          // Önceki sekmeye git
    { KEY_LEFT_CTRL, KEY_PAGE_DOWN, 0, 0 } },      // Sonraki sekmeye git
  
  // Satır 2: Ekran Görüntüsü ve Paylaşım
  { { 0, KEY_PRINT_SCREEN, 0, 0 },                 // Ekran Görüntüsü (Windows)
    { KEY_LEFT_SHIFT, KEY_PRINT_SCREEN, 0, 0 },   // Seçili Alan Ekran Görüntüsü (Windows)
    { KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 's', 0 } },  // Ekran Görüntüsü (Mac)
  
  // Satır 3: Ses ve Görüntü Kontrolleri
  { { 0, KEY_F11, 0, 0 },                          // Tam Ekran (Web Tarayıcı)
    { KEY_LEFT_ALT, KEY_TAB, 0, 0 },               // Uygulamalar arası geçiş
    { KEY_LEFT_GUI | KEY_LEFT_ALT, KEY_BACKSPACE, 0, 0 } } // Görevi bitir (Windows)
};

/*
 * CUSTOMIZATION NOTES / KUSTOMİZASYON NOTLARI:
 * 
 * Spotify / Müzik Uygulamaları:
 * { { KEY_LEFT_CTRL | KEY_LEFT_ALT, KEY_DOWN_ARROW, 0, 0 }, // Ses aç
 *   { KEY_LEFT_CTRL | KEY_LEFT_ALT, KEY_UP_ARROW, 0, 0 },   // Ses kapat
 *   { KEY_LEFT_CTRL | KEY_LEFT_ALT, KEY_LEFT_ARROW, 0, 0 } } // Önceki şarkı
 * 
 * OBS Studio (Yayın Yapma):
 * { { KEY_LEFT_CTRL | KEY_LEFT_SHIFT, 'r', 0, 0 }, // Kaydı başlat/durdur
 *   { 0, KEY_F12, 0, 0 },                          // Kaynak ayarları
 *   { 0, KEY_F11, 0, 0 } }                         // Tam ekran izleme
 * 
 * YouTube / Video İzleme:
 * { { 0, ' ', 0, 0 },                    // Oynat/Duraklat (Boşluk)
 *   { 0, 'f', 0, 0 },                    // Tam ekran
 *   { 0, 'm', 0, 0 } }                   // Sesi kapatıl
 * 
 * Ses Seviyesi Kontrolü (Windows):
 * Maalesef, Windows API doğrudan HID aracılığıyla ses kontrol etmediği için
 * Alt+F1/F2 gibi uygulama spesifik kısayolları kullanmalısınız
 */
