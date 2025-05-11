#ifndef PROX_SENSORS_H
#define PROX_SENSORS_H

#include "main.h"

void update_front_prox(uint8_t *prox_state);
uint8_t read_bit(uint8_t REG, uint8_t POS);
void write_bit(uint8_t *REG, uint8_t POS, uint8_t VAL);

#endif
