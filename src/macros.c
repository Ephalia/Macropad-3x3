#include "macros.h"

#include "tusb.h"

const uint BUTTON_GPIOS[BUTTON_COUNT] = {
    2, 3, 4,
    5, 6, 7,
    8, 9, 10
};

const char *const BUTTON_LABELS[BUTTON_COUNT] = {
    "Ctrl + C",
    "Ctrl + V",
    "Ctrl + X",
    "Alt + Tab",
    "Win + D",
    "Win + L",
    "Ctrl + Alt + T",
    "Ctrl + Shift + N",
    "Ctrl + Z"
};

const macro_binding_t MACRO_BINDINGS[BUTTON_COUNT] = {
    {KEYBOARD_MODIFIER_LEFTCTRL,        {HID_KEY_C, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTCTRL,        {HID_KEY_V, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTCTRL,        {HID_KEY_X, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTALT,         {HID_KEY_TAB, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTGUI,         {HID_KEY_D, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTGUI,         {HID_KEY_L, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, {HID_KEY_T, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, {HID_KEY_N, 0, 0}},
    {KEYBOARD_MODIFIER_LEFTCTRL,        {HID_KEY_Z, 0, 0}}
};
