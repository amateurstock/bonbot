#include "tb6612fng.h"

void update_motor(tb6612fng_pins_t motor, int32_t speed) {
    speed = (speed >= 0) ? speed : -speed;
    pwm_write(motor.PWM, speed);
    HAL_GPIO_WritePin(motor.IN1.port, motor.IN1.pin_number, (speed >= 0));
    HAL_GPIO_WritePin(motor.IN2.port, motor.IN2.pin_number, (speed >= 0));
}
