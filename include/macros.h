#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"

#define BUTTON_COUNT 9
#define MACRO_MAX_KEYS 3

typedef struct {
    uint8_t modifiers;
    uint8_t keys[MACRO_MAX_KEYS];
} macro_binding_t;

extern const uint BUTTON_GPIOS[BUTTON_COUNT];
extern const macro_binding_t MACRO_BINDINGS[BUTTON_COUNT];
extern const char *const BUTTON_LABELS[BUTTON_COUNT];
