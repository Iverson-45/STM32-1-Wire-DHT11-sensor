#pragma once

#include "stdint.h"

void OneWire_Begin();
void ReadBit(uint8_t data[5]);
void ReadData(uint8_t data[5], float *Humidity, float *Temperature);

