/**
 * @file     circular-buffer.c
 * @authors Peter Eisenhower
 * @copyright Peter Eisenhower 2013
 *
 * @brief Generic circular buffer
 */

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
#define RETURN_FAIL_IF(x)                       \
            do {                                \
                if (x) return CB_ERROR_FAIL;    \
            } while (0)
#endif

#define PRIV_OVERFLOW(cb)                               \
            do {                                        \
                if ( cb->count > cb->bufferSize ) {    \
                    cb->flags |= CB_FLAG_OVERFLOW;      \
                    return CB_ERROR_OVERFLOW;           \
            }} while (0)

/******************************************************************************
 * Local Types and Typedefs
 ******************************************************************************/

/******************************************************************************
 * Global Variables
 ******************************************************************************/

/******************************************************************************
 * Static Function Prototypes
 ******************************************************************************/
static inline void priv_incrementRead(cb_t *cb) ATTR_INLINE;
static inline void priv_incrementWrite(cb_t *cb) ATTR_INLINE;
#if QUICK_READ
static inline void priv_incQuickRead(cb_t *cb) ATTR_INLINE;
static inline void priv_incQuickWrite(cb_t *cb) ATTR_INLINE;
#endif

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

#if QUICK_READ
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
#endif

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
    cb->count = 0;

    return 0;
}

int cb_reset(cb_t *cb)
{
    RETURN_FAIL_IF (cb == NULL);

    cb->lock = 0;
    cb->readIndex = 0;
    cb->writeIndex = 0;
    cb->count = 0;

    return 0;
}

int cb_read(cb_t *cb, uint8_t *data, size_t length)
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

int cb_write(cb_t *cb, const uint8_t *data, size_t length)
{
    RETURN_FAIL_IF (cb == NULL);
    RETURN_FAIL_IF (data == NULL);
    if (length > (cb->bufferSize - cb->count))
        return CB_ERROR_MEM;

    for (size_t i = 0; i < length; i++) {
        cb->buffer[cb->writeIndex] = data[i];
        priv_incrementWrite(cb);
        PRIV_OVERFLOW(cb);
    }

    return 0;
}

int cb_isrGet(cb_t *cb, uint8_t *data, bool *isEmpty)
{
    RETURN_FAIL_IF(cb == NULL);
    RETURN_FAIL_IF(data == NULL);
    RETURN_FAIL_IF(isEmpty == NULL);


    if (cb->lock)
        return CB_ERROR_LOCK;

    cb->lock = 1;

    if (cb->count == 0) {
        *isEmpty = true;
        cb->lock = 0;
        return CB_ERROR_UNDERFLOW;
    }

    *data = cb->buffer[cb->readIndex];
    priv_incrementRead(cb);

    if (cb->count == 0)
        *isEmpty = true;
    else
        *isEmpty = false;

    cb->lock = 0;
    return 0;
}

int cb_isrPut(cb_t *cb, uint8_t data)
{
    RETURN_FAIL_IF(cb == NULL);

    if (cb->lock)
        return CB_ERROR_LOCK;

    cb->lock = 1;

    if (cb->count == cb->bufferSize) {
        return CB_ERROR_MEM;
    }

    cb->buffer[cb->writeIndex] = data;
    priv_incrementWrite(cb);
    PRIV_OVERFLOW(cb);

    cb->lock = 0;
    return 0;
}

