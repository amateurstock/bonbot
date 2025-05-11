#include "main.h"
#include "zumobot.h"

uint8_t time_check(uint32_t delay, uint32_t *timestamp) {
    uint8_t ret = (HAL_GetTick() - *timestamp >= delay);
    if (ret) { *timestamp = HAL_GetTick(); }
    return ret;
}

start_state_t get_switch_state() {
    uint8_t b0 = HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin);
    uint8_t b1 = HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) << 1;
    uint8_t b2 = HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) << 2;

    return 0b000 | b0 | b1 | b2;
}

void left_start() {
    // set motors to turn left
    while (1) {
        // wait here
        // after period of waiting, break
        break;
    }
}

void right_start() {
    // set motors to turn right
    while (1) {
        // wait here
        // after period of waiting, break
        break;
    }
}

void back_start() {
    // set motors to turn 180 deg
    while (1) {
        // wait here
        // after period of waiting, break
        break;
    }
}
