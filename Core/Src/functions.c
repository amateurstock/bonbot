#include "main.h"
#include "zumobot.h"
#include "tb6612fng.h"

extern char buf[64];
extern uint32_t length;

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
    uint8_t counter = 0;
    length = sprintf(buf, "Left starting");
    CDC_Transmit_FS((uint8_t *)buf, length + 1);
    while (1) {
        HAL_Delay(1000);
        counter += 1;
        CDC_Transmit_FS((uint8_t *)".", 2);
        if (counter == 5) {
            length = sprintf(buf, "\n\rExiting left_start()\n\r");
            CDC_Transmit_FS((uint8_t *)buf, length + 1);
            return;
        }
    }
}

void right_start() {
    uint8_t counter = 0;
    length = sprintf(buf, "Right starting");
    CDC_Transmit_FS((uint8_t *)buf, length + 1);
    while (1) {
        HAL_Delay(1000);
        counter += 1;
        CDC_Transmit_FS((uint8_t *)".", 2);
        if (counter == 5) {
            length = sprintf(buf, "\n\rExiting right_start()\n\r");
            CDC_Transmit_FS((uint8_t *)buf, length + 1);
            return;
        }
    }
}

void back_start() {
    uint8_t counter = 0;
    length = sprintf(buf, "Back starting");
    CDC_Transmit_FS((uint8_t *)buf, length + 1);
    while (1) {
        HAL_Delay(1000);
        counter += 1;
        CDC_Transmit_FS((uint8_t *)".", 2);
        if (counter == 5) {
            length = sprintf(buf, "\n\rExiting back_start()\n\r");
            CDC_Transmit_FS((uint8_t *)buf, length + 1);
            return;
        }
    }
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
