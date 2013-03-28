
#pragma once

#include <stdint.h>
#include <stdbool.h>

enum {
        CB_ERROR_NONE       =  0,
        CB_ERROR_FAIL       = -1,
        CB_ERROR_LOCK       = -2,
        CB_ERROR_UNDERFLOW  = -3,
        CB_ERROR_OVERFLOW   = -4,
        CB_ERROR_MEM        = -5,
};


typedef struct cb_s
{
    uint8_t            *buffer;
    size_t              count;
    volatile int        lock;
    size_t              readIndex;
    size_t              writeIndex;
    size_t              bufferSize;
    uint32_t            lockWait;
    uint8_t             flags;
} cb_t;

enum {
    CB_FLAG_OVERFLOW       = 0x01,
    CB_FLAG_RES1           = 0x02,
    CB_FLAG_RES2           = 0x04,
    CB_FLAG_RES3           = 0x08,
    CB_FLAG_RES4           = 0x10,
    CB_FLAG_RES5           = 0x20,
    CB_FLAG_RES6           = 0x40,
    CB_FLAG_RES7           = 0x80,
};

int cb_init(cb_t *cb, uint8_t *buffer, size_t size);
int cb_reset(cb_t *cb);

int cb_write(cb_t *cb, const uint8_t *data, size_t length);
int cb_read(cb_t *cb, uint8_t *data, size_t length);

int cb_isrGet(cb_t *cb, uint8_t *data, bool *isEmpty);
int cb_isrPut(cb_t *cb, uint8_t data);


