/*
 * Örnek: Oyun Makroları
 * 
 * Bu örnek, oyunlarda yaygın olarak kullanılan 
 * tuş kombinasyonları tanımlar.
 * 
 * HID_Macropad_3x3.ino dosyasındaki MACRO_BINDINGS 
 * dizisini bu örnekle değiştirerek kullanın.
 */

const MacroKey MACRO_BINDINGS[3][3] = {
  // Satır 1: Silah/Araç Seçimi (1-2-3 tuşları)
  { { 0, '1', 0, 0 },                      // Silah 1
    { 0, '2', 0, 0 },                      // Silah 2
    { 0, '3', 0, 0 } },                    // Silah 3
  
  // Satır 2: Hızlı Aksiyon Tuşları (Q-E-R)
  { { 0, 'q', 0, 0 },                      // Yetenekler/Aksiyon Q
    { 0, 'e', 0, 0 },                      // Yetenekler/Aksiyon E
    { 0, 'r', 0, 0 } },                    // Yeniden yükle/Aksiyon R
  
  // Satır 3: Harita/Sosyal (M-P-Tab)
  { { 0, 'm', 0, 0 },                      // Harita aç
    { 0, 'p', 0, 0 },                      // Envanteri aç / Profil
    { 0, KEY_TAB, 0, 0 } }                 // Durum ekranı / Sco tab
};

/*
 * CUSTOMIZATION NOTES / KUSTOMİZASYON NOTLARI:
 * 
 * Farklı oyun türleri için örnekler:
 * 
 * FPS Oyunları (CS:GO, Valorant):
 * { { 0, 'e', 0, 0 },          // İntearact
 *   { 0, 'c', 0, 0 },          // Radyo chat
 *   { 0, KEY_SPACE, 0, 0 } }   // Sıçra
 * 
 * RPG Oyunları (Elden Ring, Dark Souls):
 * { { 0, KEY_UP_ARROW, 0, 0 },     // Yukarı hareket
 *   { 0, KEY_LEFT_ARROW, 0, 0 },   // Sola hareket
 *   { 0, KEY_RIGHT_ARROW, 0, 0 } } // Sağa hareket
 * 
 * Strateji Oyunları (StarCraft, League):
 * { { KEY_LEFT_CTRL, '1', 0, 0 },   // Kontrol Grubu 1
 *   { KEY_LEFT_CTRL, '2', 0, 0 },   // Kontrol Grubu 2
 *   { KEY_LEFT_CTRL, '3', 0, 0 } }  // Kontrol Grubu 3
 * 
 * Kamera Kontrolü (Oyunların çoğu):
 * { { 0, KEY_UP_ARROW, 0, 0 },     // Kamera yukarı
 *   { 0, KEY_DOWN_ARROW, 0, 0 },   // Kamera aşağı
 *   { 0, KEY_LEFT_ARROW, 0, 0 } }  // Kamera sola
 */
