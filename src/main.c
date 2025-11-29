#include <stdio.h>

#include "bsp/board_api.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "tusb.h"

#include "macros.h"

#define DEBOUNCE_DELAY_US 15000
#define EVENT_QUEUE_DEPTH 16

typedef struct {
    bool stable_state;
    bool last_sample;
    absolute_time_t last_change;
} button_state_t;

typedef struct {
    uint8_t button_index;
    bool pressed;
} macro_event_t;

static button_state_t button_states[BUTTON_COUNT];
static macro_event_t event_queue[EVENT_QUEUE_DEPTH];
static uint8_t event_head = 0;
static uint8_t event_tail = 0;

static void init_buttons(void);
static void scan_buttons(void);
static void process_event_queue(void);
static void send_macro_report(uint8_t button_index, bool pressed);
static bool enqueue_event(uint8_t index, bool pressed);
static bool dequeue_event(macro_event_t *event);
static void clear_event_queue(void);

int main(void) {
    stdio_init_all();
    board_init();
    tusb_init();

    init_buttons();

    while (true) {
        tud_task();
        scan_buttons();
        process_event_queue();
        sleep_ms(1);
    }
}

static void init_buttons(void) {
    absolute_time_t now = get_absolute_time();
    for (size_t i = 0; i < BUTTON_COUNT; ++i) {
        uint gpio = BUTTON_GPIOS[i];
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);

        button_states[i] = (button_state_t){
            .stable_state = false,
            .last_sample = false,
            .last_change = now
        };
    }
}

static void scan_buttons(void) {
    absolute_time_t now = get_absolute_time();

    for (size_t i = 0; i < BUTTON_COUNT; ++i) {
        bool sample = !gpio_get(BUTTON_GPIOS[i]); // aktif-düşük
        button_state_t *state = &button_states[i];

        if (sample != state->last_sample) {
            state->last_sample = sample;
            state->last_change = now;
        }

        if (sample != state->stable_state) {
            int64_t elapsed = absolute_time_diff_us(state->last_change, now);
            if (elapsed >= DEBOUNCE_DELAY_US) {
                state->stable_state = sample;
                enqueue_event((uint8_t)i, sample);
            }
        }
    }
}

static void process_event_queue(void) {
    if (!tud_hid_ready()) {
        return;
    }

    macro_event_t event;
    if (dequeue_event(&event)) {
        send_macro_report(event.button_index, event.pressed);
    }
}

static void send_macro_report(uint8_t button_index, bool pressed) {
    const macro_binding_t *binding = &MACRO_BINDINGS[button_index];

    uint8_t keycodes[6] = {0};
    if (pressed) {
        for (size_t i = 0; i < MACRO_MAX_KEYS && i < 6; ++i) {
            keycodes[i] = binding->keys[i];
        }
    }

    tud_hid_keyboard_report(0, pressed ? binding->modifiers : 0, keycodes);
}

static bool enqueue_event(uint8_t index, bool pressed) {
    uint8_t next_head = (event_head + 1) % EVENT_QUEUE_DEPTH;
    if (next_head == event_tail) {
        // kuyruk dolu, olayı düşür
        return false;
    }

    event_queue[event_head] = (macro_event_t){
        .button_index = index,
        .pressed = pressed
    };
    event_head = next_head;
    return true;
}

static bool dequeue_event(macro_event_t *event) {
    if (event_head == event_tail) {
        return false;
    }

    *event = event_queue[event_tail];
    event_tail = (event_tail + 1) % EVENT_QUEUE_DEPTH;
    return true;
}

static void clear_event_queue(void) {
    event_head = event_tail = 0;
}

void tud_mount_cb(void) {
    clear_event_queue();
}

void tud_umount_cb(void) {
    clear_event_queue();
}

void tud_suspend_cb(bool remote_wakeup_en) {
    (void)remote_wakeup_en;
}

void tud_resume_cb(void) {}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint8_t len) {
    (void)instance;
    (void)report;
    (void)len;
    process_event_queue();
}
