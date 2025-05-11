#include "ir_sensors.h"

uint8_t prox_state = 0b00000;
uint8_t line_state = 0b00;

uint8_t update_prox(uint8_t *prox_state) {
    uint8_t ret = 0b00000;
    return ret;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    switch (GPIO_Pin) {
        // Line sensors
        case Line_Left_Pin: {
            break;
        }
        case Line_Right_Pin: {
            break;
        }

        // Proximity sensors
        case Prox_Left_Pin: {
            break;
        }
        case Prox_FL_Pin: {
            break;
        }
        case Prox_FR_Pin: {
            break;
        }
        case Prox_Right_Pin: {
            break;
        }
    }
}
