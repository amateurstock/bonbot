#include "main.h"
#include "zumobot.h"
#include "ir_sensors.h"

start_state_t state = TRACKING;
bool_t is_kat = FALSE;
bool_t is_tracking = FALSE;
char *display;
char buf[64];
uint32_t length = 0;

// GPIOs -- Ignore this eyesore, this is just to simplify things...
user_gpio_t line_left = { .port = Line_Left_GPIO_Port, .pin_number = Line_Left_Pin };
user_gpio_t line_right = { .port = Line_Right_GPIO_Port, .pin_number = Line_Right_Pin };
user_gpio_t prox_left = { .port = Prox_Left_GPIO_Port, .pin_number = Prox_Left_Pin };
user_gpio_t prox_fl = { .port = Prox_FL_GPIO_Port, .pin_number = Prox_FL_Pin };
user_gpio_t prox_ff = { .port = Prox_FF_GPIO_Port, .pin_number = Prox_FF_Pin };
user_gpio_t prox_fr = { .port = Prox_FR_GPIO_Port, .pin_number = Prox_FR_Pin };
user_gpio_t prox_right = { .port = Prox_Right_GPIO_Port, .pin_number = Prox_Right_Pin };
user_gpio_t sw1 = { .port = SW1_GPIO_Port, .pin_number = SW1_Pin };
user_gpio_t sw2 = { .port = SW2_GPIO_Port, .pin_number = SW2_Pin };
user_gpio_t sw3 = { .port = SW3_GPIO_Port, .pin_number = SW3_Pin };
user_gpio_t sw4 = { .port = SW4_GPIO_Port, .pin_number = SW4_Pin };


void setup() {
    state = get_switch_state();
}

void loop() {
    if ((sw1.port->IDR & sw1.pin_number) == GPIO_PIN_RESET) {
        is_kat = FALSE;
        is_tracking = FALSE;
        state = get_switch_state();
        display = state_to_str(state);
        length = sprintf(buf, "SW1 Off. Current mode: %s\n\r", display);
        CDC_Transmit_FS((uint8_t *)buf, length + 1);
        HAL_Delay(500);
        return;
    } else {
        switch (state) {
            case NORMAL: break;
            case LEFT_START: {
                length = sprintf(buf, "Starting left_start().\n\r");
                CDC_Transmit_FS((uint8_t *)buf, length + 1);
                left_start();
                state = NORMAL;
                is_tracking = FALSE;
                break;
            }
            case RIGHT_START: {
                length = sprintf(buf, "Starting right_start().\n\r");
                CDC_Transmit_FS((uint8_t *)buf, length + 1);
                right_start();
                state = NORMAL;
                is_tracking = FALSE;
                break;
            }
            case BACK_START: {
                length = sprintf(buf, "Starting back_start().\n\r");
                CDC_Transmit_FS((uint8_t *)buf, length + 1);
                back_start();
                state = NORMAL;
                is_tracking = FALSE;
                break;
            }
            case KAT: {
                length = sprintf(buf, "Kat mode started.\n\r");
                CDC_Transmit_FS((uint8_t *)buf, length + 1);
                state = NORMAL;
                is_kat = TRUE;
                is_tracking = FALSE;
                break;
            }
            default: {
                length = sprintf(buf, "Tracking mode started.\n\r");
                CDC_Transmit_FS((uint8_t *)buf, length + 1);
                state = NORMAL;
                is_kat = FALSE;
                is_tracking = TRUE;
                break;
            }
        }


        if (is_tracking && !is_kat) {
            length = sprintf(buf, "Normal: Tracking\n\r");
            CDC_Transmit_FS((uint8_t *)buf, length + 1);
            HAL_Delay(1000);
        } else if (!is_tracking && is_kat) {
            length = sprintf(buf, "Normal: Katting\n\r");
            CDC_Transmit_FS((uint8_t *)buf, length + 1);
            HAL_Delay(1000);
        } else if (!is_tracking && !is_kat) {
            length = sprintf(buf, "Normal mode\n\r");
            CDC_Transmit_FS((uint8_t *)buf, length + 1);
            HAL_Delay(1000);
        } else {
            length = sprintf(buf, "How the fuck does this happen?\n\r");
            CDC_Transmit_FS((uint8_t *)buf, length + 1);
            HAL_Delay(1000);
        }
    }
}

GPIO_PinState user_read_pin(user_gpio_t GPIO) {
    return HAL_GPIO_ReadPin(GPIO.port, GPIO.pin_number);
}
