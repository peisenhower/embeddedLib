
#pragma once

#include <stdint.h>

#define CB_ERROR_NONE   0
#define CB_ERROR_FAIL   (-1)
#define CB_ERROR_LOCK   (-2)



typedef struct cb_s
{
    size_t              readIndex;
    size_t              writeIndex;
    size_t              count;
    uint8_t            *buffer;
    size_t              bufferSize;
    volatile int        lock;
    uint32_t            lockWait;
    uint8_t             flags;
} cb_t;

#define CB_FLAG_OVERFLOW        (0x01)
#define CB_FLAG_RES1            (0x02)
#define CB_FLAG_RES2            (0x04)
#define CB_FLAG_RES3            (0x08)
#define CB_FLAG_RES4            (0x10)
#define CB_FLAG_RES5            (0x20)
#define CB_FLAG_RES6            (0x40)
#define CB_FLAG_RES7            (0x80)


int cb_init(cb_t *cb, uint8_t *buffer, size_t size);
int cb_write(cb_t *cb, const uint8_t *data, size_t length);
int cb_read(cb_t *cb, uint8_t *data, size_t length);



