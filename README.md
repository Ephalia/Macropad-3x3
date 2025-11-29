# Pico HID Macropad Firmware

Custom 3x3 (nine key) macropad firmware for the Raspberry Pi Pico that exposes a USB HID keyboard device. Each physical key triggers a predefined shortcut (e.g. `Ctrl+C`, `Alt+Tab`, `Win+D`) with clean debouncing so the device behaves like a plug-and-play keyboard on Windows, macOS, and Linux.

## Features

- Written in C using the official Pico SDK and TinyUSB HID stack
- Nine independent GPIO inputs arranged as a 3×3 grid
- Built-in debouncing (15&nbsp;ms) to prevent chattering
- Configurable shortcut mapping via `src/macros.c`
- USB HID keyboard descriptor for true plug‑and‑play behavior (no drivers needed)
- Thorough documentation covering hardware pinout, build, flash, and customization steps

## Repository layout

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

## Hardware requirements

- Raspberry Pi Pico / Pico W (RP2040)
- 9 × momentary push buttons (normally open)
- Wiring to connect each button between its GPIO pin and ground (internal pull-ups are enabled in firmware)
- USB cable (for power, programming, and HID communication)

## Pin mapping

Buttons are mapped row-by-row (top-left to bottom-right):

| Logical position | GPIO | Default shortcut |
| ---------------- | ---- | ---------------- |
| Row 1, Col 1     | GP2  | `Ctrl + C`       |
| Row 1, Col 2     | GP3  | `Ctrl + V`       |
| Row 1, Col 3     | GP4  | `Ctrl + X`       |
| Row 2, Col 1     | GP5  | `Alt + Tab`      |
| Row 2, Col 2     | GP6  | `Win + D`        |
| Row 2, Col 3     | GP7  | `Win + L`        |
| Row 3, Col 1     | GP8  | `Ctrl + Alt + T` |
| Row 3, Col 2     | GP9  | `Ctrl + Shift + N` |
| Row 3, Col 3     | GP10 | `Ctrl + Z`       |

See [`docs/pin_mapping.md`](docs/pin_mapping.md) for diagrams and wiring notes.

## Building the firmware

1. **Install prerequisites**
   - CMake ≥ 3.13
   - ARM GCC toolchain (e.g. `gcc-arm-none-eabi`)
   - Pico SDK dependencies (TinyUSB included)

2. **Obtain the Pico SDK**
   - Either export `PICO_SDK_PATH` to an existing checkout, **or** let CMake download it automatically (the bundled `pico_sdk_import.cmake` uses `FetchContent` when the environment variable is unset).

3. **Configure and build**

   ```bash
   cd /path/to/repo
   cmake -S . -B build
   cmake --build build
   ```

   Successful builds produce `.uf2`, `.elf`, and `.bin` artifacts inside `build/`.

4. **Flash to the Pico**
   - Hold the `BOOTSEL` button while connecting the Pico via USB.
   - A mass-storage device named `RPI-RP2` appears.
   - Copy `build/pico_hid_macropad.uf2` onto the drive. The board reboots and starts acting as a macropad immediately.

## Customizing shortcuts

- Edit `src/macros.c` to change the GPIO assignments or key combinations. Each entry defines:
  - `BUTTON_GPIOS[]`: physical pin used for that button
  - `BUTTON_LABELS[]`: human-readable name (optional but useful for documentation)
  - `MACRO_BINDINGS[]`: modifier bitmask plus up to three key codes (see `include/macros.h`)
- Supported modifier flags and key codes are defined by TinyUSB (`KEYBOARD_MODIFIER_*`, `HID_KEY_*`).
- Rebuild and flash after editing to apply the new layout.

## Debouncing strategy

Every button is sampled continuously with a 1&nbsp;ms loop. A change must remain stable for at least 15&nbsp;ms before the firmware enqueues a press/release event. This effectively filters switch bounce while preserving responsive input.

## Troubleshooting

| Issue | Resolution |
| ----- | ---------- |
| Device not detected | Ensure the Pico is flashed correctly and that the USB cable carries data. Rebuild the firmware if necessary. |
| Buttons trigger multiple times | Verify proper wiring to ground and that only one side of the button connects to the designated GPIO. Debounce logic is already enabled; stray wiring noise is the most common culprit. |
| Need different pins or shortcuts | Update `src/macros.c` and rebuild. Do not forget to adjust the documentation tables if the layout changes. |

## License

Provided under the MIT license (see repository history). Feel free to adapt the firmware for your own macropad builds.
