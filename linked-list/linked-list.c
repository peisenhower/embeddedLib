 /*************************************************************************
  * Includes
  *************************************************************************/
#include "linked-list.h"
#include <string.h>

 /*************************************************************************
  * Local Defines
  *************************************************************************/
#define CRITICAL(x)                     \
            do {                        \
                if (critical != NULL){  \
                    critical(x);}       \
            } while (0)

#define PARAM_CHECK(x)                      \
            do {                            \
                if (x){                     \
                    return LL_ERR_PARAM;}   \
            } while (0)

 /*************************************************************************
  * Local Types and Typedefs
  *************************************************************************/

 /*************************************************************************
  * Global Variables
  *************************************************************************/

 /*************************************************************************
  * Static Function Prototypes
  *************************************************************************/


 /*************************************************************************
  * Static Variables
  *************************************************************************/
static critical_t *critical = NULL;

 /*************************************************************************
  * Functions
  *************************************************************************/

int ll_create(linked_list_t *list, link_t *links[], size_t linksCount, critical_t *criticalFunction)
{

    PARAM_CHECK (list == NULL);
    PARAM_CHECK (links == NULL);
    PARAM_CHECK (length == 0);

    critical = criticalFunction;

    list->head = NULL;
    list->tail = NULL;
    list->pool = links;
    list->poolSize = linksCount;

    return LL_ERR_NONE;
}

int ll_addHead(linked_list_t *list, link_t *link)
{
    PARAM_CHECK (list == NULL);
    PARAM_CHECK (link == NULL);

    if (list->poolSize == 0)
        return LL_ERR_MEM;

    /* Check that the head is really that */
    if (list->head->before != NULL)
        return LL_ERR_NEED_RESET;

    /* Set the pointer to the second item in the list */
    link->after = list->head;
    /* Assign the new head */
    list->head = link;

    return LL_ERR_NONE;
}

int ll_addTail(linked_list_t *list, link_t *link)
{

    return LL_ERR_NONE;
}

/**
 * @brief Remove a link from the pool and return pointer to it
 * @param link [out]
 * @param list [in]
 */
int ll_reserve(linked_list_t *list, link_t **link)
{
    CRITICAL(true);
    int status = priv_reserve(list, link);
    CRITICAL(false);
    return status;
}

int priv_reserve(linked_list_t *list, link_t **link)
{
    PARAM_CHECK (list == NULL);
    PARAM_CHECK (link == NULL);

    if (list->poolSize == 0)
        return LL_ERR_MEM;

    if (list->head.before != NULL)
        return LL_ERR_NEED_RESET;

    int index;
    for (index = 0; index < list->poolSize; index++)
    {
        if (list->pool[index].state == LL_STATE_POOL)
            break;
    }
    if (index >= list->poolSize) {
        *link = NULL;
        return LL_ERR_MEM;
    }

    list->poolSize -= 1;
    *link = list->pool[index];
    *link->state = LL_STATE_RESERVED;

    /* Set the pointer to the second item in the list */
    link->after = list->head;
    /* Assign the new head */
    list->head = link;

    return LL_ERR_NONE;
}

/**
 * @brief Restore a link back to the pool.
 */
static int priv_poolAdd(linked_list_t *list, link_t *link)
{
    for (int i = 0; i < list->poolSize; i++)
    {
        /* match the pointers */
        if (&list->pool[i] == add)
        {
            list->pool[i].privFlags |= LL_FLAG_PRIV_POOL;
            list->poolSize += 1;
            return LL_ERR_NONE;
        }
    }
    return LL_ERR_FAILED;
}




