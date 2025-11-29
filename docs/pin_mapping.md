# Pin Mapping & Wiring Guide

The macropad uses nine independent GPIO pins on the Raspberry Pi Pico. Buttons are arranged as a 3×3 grid (row-major order) and wired as **active-low** inputs (each button shorts the GPIO to ground when pressed). Internal pull-ups are enabled in firmware, so no external resistors are required.

## GPIO layout

| Button position | GPIO | Default macro         |
| --------------- | ---- | --------------------- |
| Row 1, Column 1 | GP2  | `Ctrl + C`            |
| Row 1, Column 2 | GP3  | `Ctrl + V`            |
| Row 1, Column 3 | GP4  | `Ctrl + X`            |
| Row 2, Column 1 | GP5  | `Alt + Tab`           |
| Row 2, Column 2 | GP6  | `Win + D`             |
| Row 2, Column 3 | GP7  | `Win + L`             |
| Row 3, Column 1 | GP8  | `Ctrl + Alt + T`      |
| Row 3, Column 2 | GP9  | `Ctrl + Shift + N`    |
| Row 3, Column 3 | GP10 | `Ctrl + Z`            |

```
Top of macropad
┌─────┬─────┬─────┐
│ GP2 │ GP3 │ GP4 │
├─────┼─────┼─────┤
│ GP5 │ GP6 │ GP7 │
├─────┼─────┼─────┤
│ GP8 │ GP9 │ GP10│
└─────┴─────┴─────┘
``` 

## Wiring instructions

1. Connect one leg of each push button to its assigned GPIO pin.
2. Connect the other leg of every button to a common ground rail.
3. Keep wire runs short or twisted in pairs to minimize noise.
4. Leave the Pico’s onboard LED (GP25) and SWD pins untouched to avoid conflicts.

Modifying the layout is as simple as editing `BUTTON_GPIOS` in `src/macros.c` and updating this document accordingly.
