#ifndef TB6612FNG_H
#define TB6612FNG_H

#include "main.h"
#include "pwm.h"
#include "zumobot.h"

typedef struct {
    user_gpio_t IN1;
    user_gpio_t IN2;
    user_gpio_t STBY;
    user_gpio_t PWM;
} tb6612fng_pins_t;

#endif
