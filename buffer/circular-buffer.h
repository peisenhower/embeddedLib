
#pragma once

#include <stdint.h>

#define CB_ERROR_NONE   0
#define CB_ERROR_FAIL   (-1)
#define CB_ERROR_LOCK   (-2)



typedef struct cb_s
{
    size_t              read_index;
    size_t              write_index;
    uint8_t            *buffer;
    size_t              buffer_size;
    int                 lock;
} cb_t;





int cb_init(cb_t *cb, uint8_t *buffer, size_t size);

