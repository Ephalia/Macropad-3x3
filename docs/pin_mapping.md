# Pin Eşlemesi & Kablolama Kılavuzu

Macropad, Raspberry Pi Pico üzerinde dokuz bağımsız GPIO pini kullanır. Düğmeler 3×3 ızgara şeklinde (satır-öncelikli sıralama) düzenlenmiştir ve **aktif-düşük** girişler olarak kablolıdır (her düğme basıldığında GPIO'yu toprağa kısa devre yapar). Dahili pull-up'lar firmware'de etkinleştirilmiştir, bu nedenle harici direnç gerekmez.

## GPIO düzeni

| Düğme konumu    | GPIO | Varsayılan makro      |
| --------------- | ---- | --------------------- |
| Satır 1, Sütun 1 | GP2  | `Ctrl + C`            |
| Satır 1, Sütun 2 | GP3  | `Ctrl + V`            |
| Satır 1, Sütun 3 | GP4  | `Ctrl + X`            |
| Satır 2, Sütun 1 | GP5  | `Alt + Tab`           |
| Satır 2, Sütun 2 | GP6  | `Win + D`             |
| Satır 2, Sütun 3 | GP7  | `Win + L`             |
| Satır 3, Sütun 1 | GP8  | `Ctrl + Alt + T`      |
| Satır 3, Sütun 2 | GP9  | `Ctrl + Shift + N`    |
| Satır 3, Sütun 3 | GP10 | `Ctrl + Z`            |

```
Macropad'in üst kısmı
┌─────┬─────┬─────┐
│ GP2 │ GP3 │ GP4 │
├─────┼─────┼─────┤
│ GP5 │ GP6 │ GP7 │
├─────┼─────┼─────┤
│ GP8 │ GP9 │ GP10│
└─────┴─────┴─────┘
``` 

## Kablolama talimatları

1. Her basmalı düğmenin bir bacağını atanan GPIO pinine bağlayın.
2. Her düğmenin diğer bacağını ortak bir toprak rayına bağlayın.
3. Gürültüyü en aza indirmek için kablo bağlantılarını kısa tutun veya çiftler halinde bükülerek kullanın.
4. Çakışmayı önlemek için Pico'nun yerleşik LED'ini (GP25) ve SWD pinlerini dokunulmamış bırakın.

Düzeni değiştirmek, `src/macros.c` dosyasındaki `BUTTON_GPIOS` değerini düzenlemek ve bu dokümanı buna göre güncellemek kadar basittir.
