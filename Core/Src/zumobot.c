#include "main.h"
#include "zumobot.h"
#include "ir_sensors.h"

start_state_t state = TRACKING;
bool_t is_kat = FALSE;
bool_t is_tracking = FALSE;
bool_t is_attacking = FALSE;
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
        return;
    } else {
        switch (state) {
            case NORMAL: break;
            case LEFT_START: {
                left_start();
                state = NORMAL;
                is_tracking = FALSE;
                break;
            }
            case RIGHT_START: {
                right_start();
                state = NORMAL;
                is_tracking = FALSE;
                break;
            }
            case BACK_START: {
                back_start();
                state = NORMAL;
                is_tracking = FALSE;
                break;
            }
            case KAT: {
                state = NORMAL;
                is_kat = TRUE;
                is_tracking = FALSE;
                break;
            }
            default: {
                state = NORMAL;
                is_kat = FALSE;
                is_tracking = TRUE;
                break;
            }
        }

        if (is_attacking) {
            attacking();
        }

        if (is_tracking && !is_kat) { // Tracking mode
            tracking();
        } else if (!is_tracking && is_kat) { // Katting mode
            katting();
        } else if (!is_tracking && !is_kat) { // Normal mode
            normal();
        } else { // Invalid mode
            tracking();
        }
    }
}

GPIO_PinState user_read_pin(user_gpio_t GPIO) {
    return HAL_GPIO_ReadPin(GPIO.port, GPIO.pin_number);
}
