#include "zumobot.h"
#include "ir_sensors.h"

extern user_gpio_t line_left;
extern user_gpio_t line_right;
extern user_gpio_t prox_left;
extern user_gpio_t prox_fl;
extern user_gpio_t prox_ff;
extern user_gpio_t prox_fr;
extern user_gpio_t prox_right;

//                     LLFRR
uint8_t prox_state = 0b00000;

//                     LR
uint8_t line_state = 0b00;

void update_front_prox(uint8_t *prox_state) {
    uint8_t is_on = user_read_pin(prox_ff);
    if (is_on) {
        *prox_state = *prox_state | (1 << 2);
    } else {
        *prox_state = *prox_state & ~(1 << 2);
    }
}

uint8_t read_bit(uint8_t REG, uint8_t POS) {
    return ((REG >> POS) & 1);
}

void write_bit(uint8_t *REG, uint8_t POS, uint8_t VAL) {
    if (VAL) *REG = *REG | (1 << POS);
    else *REG = *REG & ~(1 << POS);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    uint8_t previous;
    uint8_t current;
    uint8_t pos;
    switch (GPIO_Pin) {

        // Line sensors
        case Line_Left_Pin: {
            pos = 1;
            previous = read_bit(line_state, pos);
            current = user_read_pin(line_left);
            if (current == 1 && previous == 0) {
                write_bit(&line_state, pos, 1);
            } else if (current == 0 && previous == 1) {
                write_bit(&line_state, pos, 0);
            }
            break;
        }
        case Line_Right_Pin: {
            pos = 0;
            previous = read_bit(line_state, pos);
            current = user_read_pin(line_left);
            if (current == 1 && previous == 0) {
                write_bit(&line_state, pos, 1);
            } else if (current == 0 && previous == 1) {
                write_bit(&line_state, pos, 0);
            }
            break;
        }

        // Proximity sensors -- Pos 0, 1, 3, 4 are only covered.
        // Pos 2 is up for manual polling in the main loop
        case Prox_Left_Pin: {
            pos = 4;
            previous = read_bit(prox_state, pos);
            current = user_read_pin(line_left);
            if (current == 1 && previous == 0) {
                write_bit(&line_state, pos, 1);
            } else if (current == 0 && previous == 1) {
                write_bit(&line_state, pos, 0);
            }
            break;
        }
        case Prox_FL_Pin: {
            pos = 3;
            previous = read_bit(prox_state, pos);
            current = user_read_pin(line_left);
            if (current == 1 && previous == 0) {
                write_bit(&line_state, pos, 1);
            } else if (current == 0 && previous == 1) {
                write_bit(&line_state, pos, 0);
            }
            break;
        }
        case Prox_FR_Pin: {
            pos = 1;
            previous = read_bit(prox_state, pos);
            current = user_read_pin(line_left);
            if (current == 1 && previous == 0) {
                write_bit(&line_state, pos, 1);
            } else if (current == 0 && previous == 1) {
                write_bit(&line_state, pos, 0);
            }
            break;
        }
        case Prox_Right_Pin: {
            pos = 0;
            previous = read_bit(prox_state, pos);
            current = user_read_pin(line_left);
            if (current == 1 && previous == 0) {
                write_bit(&line_state, pos, 1);
            } else if (current == 0 && previous == 1) {
                write_bit(&line_state, pos, 0);
            }
            break;
        }

    }
}
