
#pragma once


/**
 * @file linked-list.h
 *
 * Linked List header file.
 * Link can be in one for 3 states.
 * Pool: waiting to be used.
 * Reserved: taken by the application being manipulated
 * List: In the list waiting to be dequeued.
 *
 * Typcially the application will pull a link from the pool and
 * reserve the link. The application will fill in the data and push
 * the link to the list. Another program can get items from the list which
 * will come out as reserved. When done with the data it can be released back
 * to the pool.
 *
 * POOL -> RESERVED -> LIST -> RESERVED -> POOL ...
 *
 * From the list another part of the application or an ISR will dequeue the data
 * and return it to the pool. Alternatively the application could decide the 
 * reserved message is no longer needed and push it back to the pool.
 *
 * Flags are for the application to use. privFlags are for the link list functions.
 *
 * @warning It is possible for the application to reserve data and not return it
 *          to the pool or list.
 */

#include <stdbool.h>
#include <stdint.h>


typedef enum {
    LL_STATE_UNKNOWN    = 0,
    LL_STATE_POOL       = 1,
    LL_STATE_RESERVED   = 2,
    LL_STATE_LIST       = 3,
} ll_state_t


typedef struct link_s
{
    volatile struct link_s   *before;
    volatile struct link_s   *after;
    volatile uint8_t 	      state;
    volatile uint8_t          flags;
    uint8_t                  *data;
    size_t                    size;
} link_t;

typedef struct linked_list_s
{
    volatile link_t      *head;
    volatile link_t      *tail;
    link_t               *pool[];
    size_t                poolSize;
} linked_list_t;


enum
{
    LL_ERR_NONE         =  0,
    LL_ERR_FAILED       = -1,
    LL_ERR_MEM          = -2,
    LL_ERR_PARAM        = -3,
    LL_ERR_NEED_RESET   = -4,
    LL_ERR_NOT_IMPL     = -5,
};


/**
 * If an ISR is accessing the list along with the application the
 * critical should disable the ISR to prevent data corruption.
 * If the link list is only being accessed by a single threaded 
 * application then the function can be null.
 */
typedef void (*critical_t)(bool enable);


