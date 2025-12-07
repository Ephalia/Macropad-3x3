/*
 * Örnek: Verimlilik Makroları
 * 
 * Bu örnek, yazı işlemleri ve verimlilik uygulamalarında 
 * yaygın olarak kullanılan tuş kombinasyonları tanımlar.
 * 
 * HID_Macropad_3x3.ino dosyasındaki MACRO_BINDINGS 
 * dizisini bu örnekle değiştirerek kullanın.
 */

const MacroKey MACRO_BINDINGS[3][3] = {
  // Satır 1: Temel Editörler (Kes/Kopyala/Yapıştır)
  { { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'x', 0, 0 },          // Kes
    { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'c', 0, 0 },          // Kopyala
    { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'v', 0, 0 } },        // Yapıştır
  
  // Satır 2: Dosya Operasyonları
  { { MACRO_KEYBOARD, KEY_LEFT_CTRL, 's', 0, 0 },          // Kaydet
    { MACRO_KEYBOARD, KEY_LEFT_CTRL | KEY_LEFT_SHIFT, 's', 0, 0 }, // Farklı kaydet
    { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'n', 0, 0 } },        // Yeni dosya
  
  // Satır 3: Geri Al / İleri Al / Redo
  { { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'z', 0, 0 },          // Geri Al (Undo)
    { MACRO_KEYBOARD, KEY_LEFT_CTRL | KEY_LEFT_SHIFT, 'z', 0, 0 }, // İleri Al (Redo)
    { MACRO_KEYBOARD, KEY_LEFT_CTRL, 'a', 0, 0 } }         // Tümünü Seç
};

/*
 * CUSTOMIZATION NOTES / KUSTOMİZASYON NOTLARI:
 * 
 * Bu makrolar, Microsoft Office, Google Docs, 
 * VS Code ve benzeri yazı editörlerinde standart 
 * kısayollardır.
 * 
 * Farklı uygulamalar için uygulamaya özel 
 * kısayolları kullanabilirsiniz:
 * 
 * Slack İçin:
 * - Ctrl+Shift+M: Sessiz kişi / Grup
 * - Ctrl+Shift+L: Çıkış yap
 * 
 * Gmail İçin:
 * - g + i: Gelen kutusu
 * - g + d: Taslaklar
 * - Ctrl+Enter: Gönder
 * 
 * Notion İçin:
 * - Ctrl+Shift+D: Koyu mod
 * - Ctrl+/: Komut paletini aç
 */
