#include "main.h"
#include "zumobot.h"

start_state_t state = TRACKING;
bool_t is_kat = FALSE;
bool_t is_tracking = FALSE;

void setup() {
    state = get_switch_state();
}

void loop() {
    if ((SW1_GPIO_Port->IDR & SW1_Pin) == GPIO_PIN_RESET) {
        state = get_switch_state();
    } else {
        switch (state) {

            case NORMAL: break;

            case LEFT_START: {
                left_start();
                state = NORMAL;
                break;
            }

            case RIGHT_START: {
                right_start();
                state = NORMAL;
                break;
            }


            case BACK_START: {
                back_start();
                state = NORMAL;
                break;
            }

            case KAT: {
                is_kat = TRUE;
                state = NORMAL;
                break;
            }

            default: {
                is_tracking = TRUE;
                state = NORMAL;
                break;
            }

        }
    }
}
