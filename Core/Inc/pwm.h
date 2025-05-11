#ifndef PWM_H
#define PWM_H

#include "main.h"
#include "zumobot.h"

void pwm_write(user_gpio_t pin, int32_t speed);

#endif
