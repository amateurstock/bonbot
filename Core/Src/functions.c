#include "main.h"
#include "zumobot.h"
#include "tb6612fng.h"

extern char buf[64];
extern uint32_t length;
extern uint8_t prox_state;
extern uint8_t line_state;
extern bool_t is_attacking;

uint8_t time_check(uint32_t delay, uint32_t *timestamp) {
    uint8_t ret = (HAL_GetTick() - *timestamp >= delay);
    if (ret) { *timestamp = HAL_GetTick(); }
    return ret;
}

start_state_t get_switch_state() {
    uint8_t b0 = HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin);
    uint8_t b1 = HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) << 1;
    uint8_t b2 = HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) << 2;

    return 0b000 | b0 | b1 | b2;
}

void left_start() {
    uint32_t time_start = HAL_GetTick();
    debug_message("left_start, motor control");
    while (1) {
        update_front_prox(&prox_state);
        if (prox_state) {
            is_attacking = TRUE;
            return;
        } else if (HAL_GetTick() - time_start >= 1000) {
            return;
        }
    }
}

void right_start() {
    uint32_t time_start = HAL_GetTick();
    debug_message("right_start, motor control");
    while (1) {
        update_front_prox(&prox_state);
        if (prox_state) {
            is_attacking = TRUE;
            return;
        } else if (HAL_GetTick() - time_start >= 1000) {
            return;
        }
    }
}

void back_start() {
    uint32_t time_start = HAL_GetTick();
    debug_message("back_start, motor control");
    while (1) {
        update_front_prox(&prox_state);
        if (prox_state) {
            is_attacking = TRUE;
            return;
        } else if (HAL_GetTick() - time_start >= 1000) {
            return;
        }
    }
}

void attacking() {
    while (1) {
        update_front_prox(&prox_state);
        if (prox_state) {
            debug_message("Attacking...");
            HAL_Delay(125);
        } else {
            radar();
        }
        if ((sw1.port->IDR & sw1.pin_number) == GPIO_PIN_RESET) {
            is_attacking = FALSE;
            return;
        }
    }
}

void radar() {
    debug_message("radar, motor control");
    while (1) {
        update_front_prox(&prox_state);
        if (prox_state) return;
        debug_message("radarig");
        HAL_Delay(500);
    }
}

void tracking() {
}

void katting() {
}

void normal() {
    debug_message("normal, motor control");
    while (1) {
        update_front_prox(&prox_state);
        if (prox_state) {
            is_attacking = TRUE;
            return;
        }
        if (line_state) {
            turn_around();
            debug_message("normal, motor control");
        }
        if ((sw1.port->IDR & sw1.pin_number) == GPIO_PIN_RESET) {
            return;
        }
    }
}

void turn_around() {
    debug_message("turn_around, motor control");
    HAL_Delay(500);
    debug_message("turn_around, motor control");
    HAL_Delay(500);
    debug_message("turn_around, motor control");
    return;
}

char *state_to_str(start_state_t cmd) {
    switch (cmd) {
        case NORMAL: return "Normal";
        case LEFT_START: return "Left start";
        case RIGHT_START: return "Right start";
        case BACK_START: return "Back start";
        case KAT: return "Kat";
        case TRACKING: return "Tracking";
        default: return "Invalid";
    }
}

void debug_message(const char *MSG) {
    length = sprintf(buf, "%s\n\r", MSG);
    CDC_FS_Transmit((uint8_t *)buf, length + 1);
}
