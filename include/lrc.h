#pragma once
#include <stdint.h>
#include <string.h>

#define LRC_INITIAL 0xFF

uint8_t el_lrc8 (uint8_t initial, const uint8_t *data, size_t length);
