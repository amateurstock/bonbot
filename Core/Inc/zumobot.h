#ifndef ZUMOBOT_H
#define ZUMOBOT_H

#include "stm32f103xb.h"
#include "usbd_cdc_if.h"
#include "stdio.h"

typedef enum {
    NORMAL      = 0b010,
    LEFT_START  = 0b100,
    RIGHT_START = 0b001,
    BACK_START  = 0b101,
    KAT         = 0b111,
    TRACKING    = 0b000
} start_state_t;

typedef enum {
    FALSE,
    TRUE
} bool_t;

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin_number;
} user_gpio_t;

// Exported functions
void setup();
void loop();
uint8_t time_check(uint32_t delay, uint32_t *timestamp);
void left_start();
void right_start();
void back_start();
start_state_t get_switch_state();
char *state_to_str(start_state_t cmd);

#endif
