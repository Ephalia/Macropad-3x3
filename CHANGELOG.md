# Changelog - Arduino Pro Micro 3x3 HID Macropad

All notable changes to this project will be documented in this file.

## [2.0.0] - 2024 - D0-D8 Pin Configuration + Diode Support

### 🎯 Major Changes

#### Pin Configuration Update
- **Changed**: Pin mapping from scattered pins (D4, D6, D10, D16, D14, D15, D9, D5, D3) to sequential pins (D0-D8)
- **Benefit**: Easier to remember, cleaner wiring, more logical layout
- **New Pin Mapping**:
  - D0 (RX): Volume Down
  - D1 (TX): Volume Up
  - D2 (SDA): Mute
  - D3: Previous
  - D4: Play/Pause
  - D5: Next
  - D6: Alt+F4
  - D7: Windows+D
  - D8: Windows+L

#### Diode Support Added
- **New**: Firmware now supports BOTH diode-less and diode configurations
- **Important**: Same firmware works for both setups - no code changes needed
- **Diode Type**: 1N4148 (9 pieces for diode configuration)
- **Added**: Comprehensive documentation for both setup options

### ✨ New Features

1. **Dual Hardware Support**
   - Diode-less setup (simple, fast, low-cost)
   - Diode setup (professional, ghost-proof, safe)
   - Same firmware works for both

2. **Enhanced Documentation**
   - New `docs/WIRING_GUIDE.md` - Step-by-step wiring guide
   - Updated `README.md` - Comprehensive documentation with both setup options
   - Updated `docs/pin_mapping.md` - New pin mapping and diode wiring diagrams
   - Turkish language support throughout

3. **Debounce Configuration Update**
   - Changed from 15ms to 20ms default
   - Adjustable from 20-50ms
   - Better stability with various switch types

### 📝 Documentation Updates

#### README.md
- Added hardware setup options section
- Added diode-less vs diode comparison table
- Added detailed ASCII art wiring diagrams for both setups
- Added diode direction identification guide
- Added switching guide (diode-less ↔ diode)
- Updated pin mapping table (D0-D8)
- Updated troubleshooting section

#### docs/pin_mapping.md
- Complete rewrite for D0-D8 configuration
- Added diode-less wiring schema
- Added diode wiring schema
- Added 1N4148 diode identification guide
- Added multimeter testing instructions
- Updated pinout diagram
- Added D0/D1 serial port conflict warning

#### docs/WIRING_GUIDE.md (NEW)
- Comprehensive step-by-step wiring guide
- Material requirements list
- Diode-less setup instructions
- Diode setup instructions
- Physical assembly steps for breadboard
- Connection testing procedures
- Troubleshooting for wiring issues
- PCB transition tips
- 3D printable case suggestions

#### IMPLEMENTATION_SUMMARY.md
- Updated for version 2.0
- Added all 10 acceptance criteria
- Added diode support documentation
- Updated technical specifications
- Added "new features" section

#### PROJECT_STRUCTURE.md
- Added WIRING_GUIDE.md entry
- Updated pin_mapping.md description
- Updated HID_Macropad_3x3.ino description

### 🔧 Technical Changes

#### Firmware (HID_Macropad_3x3.ino)
```cpp
// Old pin configuration
const int BUTTON_PINS[3][3] = {
  { 4,  6, 10 },
  { 16, 14, 15 },
  { 9, 5, 3 }
};

// New pin configuration
const int BUTTON_PINS[3][3] = {
  { 0,  1,  2 },  // Row 1: D0, D1, D2
  { 3,  4,  5 },  // Row 2: D3, D4, D5
  { 6,  7,  8 }   // Row 3: D6, D7, D8
};
```

#### Debounce Time
```cpp
// Old: 15ms
const unsigned long DEBOUNCE_TIME = 15;

// New: 20ms (adjustable 20-50ms)
const unsigned long DEBOUNCE_TIME = 20;
```

#### Comments
- Added diode support information in file header
- Added wiring options (diode-less and diode)
- Updated pin configuration comments

### 🛠️ Hardware Compatibility

**Both configurations work with the same firmware:**
- **Diode-less**: Switch Pin 1 → GPIO, Switch Pin 2 → GND
- **Diode**: Switch Pin 1 → Diode Cathode (-), Diode Anode (+) → GPIO, Switch Pin 2 → GND

**INPUT_PULLUP mode** handles both configurations automatically.

### 📊 Comparison: Old vs New

| Feature | Version 1.0 | Version 2.0 |
|---------|-------------|-------------|
| Pin Configuration | D4,D6,D10,D16,D14,D15,D9,D5,D3 | D0,D1,D2,D3,D4,D5,D6,D7,D8 |
| Pin Layout | Scattered | Sequential |
| Diode Support | No | Yes (optional) |
| Debounce Time | 15ms (fixed) | 20ms (adjustable 20-50ms) |
| Wiring Guide | Basic | Comprehensive step-by-step |
| Setup Options | 1 (diode-less only) | 2 (diode-less + diode) |
| Documentation | Standard | Extensive + Turkish |

### ⚠️ Breaking Changes

**IMPORTANT**: Pin configuration has changed. If you're upgrading from version 1.0:

1. **Re-wire your macropad** according to the new D0-D8 pin mapping
2. **Update firmware** to version 2.0
3. **No code changes needed** for diode-less to diode transition

### 🎓 Migration Guide

#### From Version 1.0 to 2.0

**Step 1: Backup**
- Save your current configuration
- Note any custom macro bindings

**Step 2: Re-wire**
- Disconnect Arduino from USB
- Change wiring according to new pin mapping:
  - Old D4 → New D0
  - Old D6 → New D1
  - Old D10 → New D2
  - Old D16 → New D3
  - Old D14 → New D4
  - Old D15 → New D5
  - Old D9 → New D6
  - Old D5 → New D7
  - Old D3 → New D8

**Step 3: Upload New Firmware**
- Open HID_Macropad_3x3.ino (version 2.0)
- Upload to Arduino Pro Micro
- Test all switches

**Step 4 (Optional): Add Diodes**
- If you want diode protection, follow the diode setup guide in docs/WIRING_GUIDE.md
- No firmware changes needed

### 🐛 Bug Fixes

- Improved debounce stability (15ms → 20ms)
- Added D0/D1 serial port conflict warning
- Clarified pull-up resistor usage (internal)

### 📚 New Documentation Files

1. `docs/WIRING_GUIDE.md` - Complete wiring guide for both setups
2. Updated all existing documentation for version 2.0

### 🔮 Future Plans

- Matrix keyboard support (when using diode configuration)
- Additional example configurations
- PCB design files
- 3D printable case design

---

## [1.0.0] - 2024 - Initial Release

### Initial Features

- Arduino Pro Micro 3x3 HID Macropad firmware
- 9 button support (3x3 grid)
- USB HID Keyboard support
- Media controls (Volume, Play/Pause, Next/Previous)
- System shortcuts (Alt+F4, Win+D, Win+L)
- 15ms debouncing
- Plug-and-play (no driver required)
- Turkish documentation

### Initial Pin Configuration

- D4, D6, D10 (Row 1)
- D16, D14, D15 (Row 2)
- D9, D5, D3 (Row 3)

### Initial Documentation

- README.md (Turkish)
- docs/pin_mapping.md
- docs/ARDUINO_IDE_SETUP.md
- docs/TROUBLESHOOTING.md
- examples/ (3 example configurations)

---

**Legend:**
- 🎯 Major Changes
- ✨ New Features
- 📝 Documentation Updates
- 🔧 Technical Changes
- 🛠️ Hardware Compatibility
- 📊 Comparison
- ⚠️ Breaking Changes
- 🎓 Migration Guide
- 🐛 Bug Fixes
- 🔮 Future Plans
