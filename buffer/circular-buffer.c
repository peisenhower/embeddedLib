

/******************************************************************************
 * Includes 
 ******************************************************************************/
#include <stdio.h>
#include "circular-buffer.h"
#include "compiler.h"
#include "common.h"

/******************************************************************************
 * Local Defines
 ******************************************************************************/
#ifndef RETURN_FAIL_IF
#define RETURN_FAIL_IF(x) do {\
                            if (x) return -1;\
                          } while (0)
#endif

/******************************************************************************
 * Local Types and Typedefs
 ******************************************************************************/
#define PRIV_OVERFLOW(cb)       \
            do {                \
                if ( cb->count >= cb->bufferSize ) { \
                    cb->flags |= CB_FLAG_OVERFLOW; \
                    return -1;  \
            }} while (0)

/******************************************************************************
 * Global Variables
 ******************************************************************************/

/******************************************************************************
 * Static Function Prototypes
 ******************************************************************************/
static inline void priv_incrementRead(cb_t *cb) ATTR_INLINE;
static inline void priv_incrementWrite(cb_t *cb) ATTR_INLINE;
static inline void priv_incQuickRead(cb_t *cb) ATTR_INLINE;
static inline void priv_incQuickWrite(cb_t *cb) ATTR_INLINE;

/******************************************************************************
 * Static Variables 
 ******************************************************************************/

/******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * increment and wrap
 */
static inline void priv_incrementRead(cb_t *cb)
{
    cb->readIndex++;
    cb->count--;
    if (cb->readIndex >= cb->bufferSize)
        cb->readIndex = 0;
}

/**
 * increment and wrap
 */
static inline void priv_incrementWrite(cb_t *cb)
{
    cb->writeIndex++;
    cb->count++;
    if (cb->writeIndex >= cb->bufferSize)
        cb->writeIndex = 0;
}

/**
 * Only to be used if buffer is a power of 2
 */
static inline void priv_incQuickRead(cb_t *cb)
{
    cb->readIndex++;
    cb->readIndex &= ~cb->bufferSize;
}

/**
 * Only to be used if buffer is a power of 2
 */
static inline void priv_incQuickWrite(cb_t *cb)
{
    cb->writeIndex++;
    cb->writeIndex &= ~cb->bufferSize;
}

/**
 * fill out the struct
 */
int cb_init(cb_t *cb, uint8_t *buffer, size_t size)
{
    RETURN_FAIL_IF (cb == NULL);
    RETURN_FAIL_IF (buffer == NULL);
    RETURN_FAIL_IF (size == 0);

    cb->buffer = buffer;
    cb->bufferSize = size;
    cb->lock = 0;
    cb->readIndex = 0;
    cb->writeIndex = 0;

    return 0;
}

int
cb_read(cb_t *cb, uint8_t *data, size_t length)
{
    RETURN_FAIL_IF (cb == NULL);
    RETURN_FAIL_IF (data == NULL);
    RETURN_FAIL_IF (length > cb->count);

    if (length == 0)
        return 0;
    for (size_t i = 0; i < length; i++) {
        data[i] = cb->buffer[cb->readIndex];
        priv_incrementRead(cb);
        PRIV_OVERFLOW(cb);
    }

    return 0;
}

int
cb_write(cb_t *cb, const uint8_t *data, size_t length)
{
    RETURN_FAIL_IF (cb == NULL);
    RETURN_FAIL_IF (data == NULL);
    RETURN_FAIL_IF (length > (cb->bufferSize - cb->count));

    for (size_t i = 0; i < length; i++) {
        cb->buffer[cb->writeIndex] = data[i];
        priv_incrementWrite(cb);
        PRIV_OVERFLOW(cb);
    }

    return 0;
}



