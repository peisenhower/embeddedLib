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
static int priv_reserve(linked_list_t *list, link_t **link);
static int priv_release(linked_list_t *list, link_t *link);
static int priv_pushTail(linked_list_t *list, link_t *link);
static int priv_pushHead(linked_list_t *list, link_t *link);
static int priv_pullTail(linked_list_t *list, link_t **link);
static int priv_pullHead(linked_list_t *list, link_t **link);

 /*************************************************************************
  * Static Variables
  *************************************************************************/
static critical_t critical = NULL;

 /*************************************************************************
  * Functions
  *************************************************************************/


/*******************************************************************************
* Create
*******************************************************************************/
int ll_create(linked_list_t *list, link_t *links[], size_t linksCount, critical_t criticalFunction)
{
    PARAM_CHECK (list == NULL);
    PARAM_CHECK (links == NULL);
    PARAM_CHECK (linksCount == 0);

    critical = criticalFunction;

    list->head = NULL;
    list->tail = NULL;
    list->pool = links;
    list->poolSize = linksCount;

    for (int i = 0; i < list->poolSize; i++) {
        list->pool[i]->state = LL_STATE_POOL;
        list->pool[i]->flags = 0;
        list->pool[i]->before = NULL;
        list->pool[i]->after = NULL;
    }

    return LL_ERR_NONE;
}

/*******************************************************************************
* Pull
*******************************************************************************/
int ll_pullHead(linked_list_t *list, link_t **link)
{
    CRITICAL(true);
    int status = priv_pullHead(list, link);
    CRITICAL(false);
    return status;
}
static int priv_pullHead(linked_list_t *list, link_t **link)
{
    PARAM_CHECK(list == NULL);
    PARAM_CHECK(link == NULL);
    PARAM_CHECK(list->head == NULL);

    *link = list->head;

    if (list->head == list->tail){
        /* Only item in queue */
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->after;
        list->head->before = NULL;
    }

    (*link)->after = NULL;
    (*link)->before = NULL;
    (*link)->state = LL_STATE_RESERVED;
    return LL_ERR_NONE;
}

int ll_pullTail(linked_list_t *list, link_t **link)
{
    CRITICAL(true);
    int status = priv_pullTail(list, link);
    CRITICAL(false);
    return status;
}
int priv_pullTail(linked_list_t *list, link_t **link)
{
    PARAM_CHECK(list == NULL);
    PARAM_CHECK(link == NULL);
    PARAM_CHECK(list->tail == NULL);

    *link = list->tail;

    if (list->head == list->tail){
        /* Only item in queue */
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->before;
        list->tail->after = NULL;
    }

    (*link)->after = NULL;
    (*link)->before = NULL;
    (*link)->state = LL_STATE_RESERVED;
    return LL_ERR_NONE;
}

/*******************************************************************************
* Push
*******************************************************************************/
int ll_pushHead(linked_list_t *list, link_t *link)
{
    CRITICAL(true);
    int status = priv_pushHead(list, link);
    CRITICAL(false);
    return status;
}

static int priv_pushHead(linked_list_t *list, link_t *link)
{
    PARAM_CHECK (list == NULL);
    PARAM_CHECK (link == NULL);

    if (list->head == list->tail){
        /* Only item in the list, its both head and tail */
        list->head = link;
        list->tail = link;
        link->before = NULL;
        link->after = NULL;
    } else {
        /* Set the pointer to the second item in the list */
        link->after = list->head;
        link->before = NULL;

        /* Update the previous head */
        list->head->before = link;
        /* Assign the new head */
        list->head = link;
    }

    link->state = LL_STATE_LIST;
    return LL_ERR_NONE;
}

int ll_pushTail(linked_list_t *list, link_t *link)
{
    CRITICAL(true);
    int status = priv_pushTail(list, link);
    CRITICAL(false);
    return status;
}

static int priv_pushTail(linked_list_t *list, link_t *link)
{
    PARAM_CHECK (list == NULL);
    PARAM_CHECK (link == NULL);

    if (list->head == list->tail){
        /* Only item in the list, its both head and tail */
        list->head = link;
        list->tail = link;
        link->before = NULL;
        link->after = NULL;
    } else {
        /* Set the pointer to the second to last item in the list */
        link->before = list->tail;
        link->after = NULL;
        /* Update the previous tail */
        list->tail->after = link;
        /* Assign the new head */
        list->tail = link;
    }

    if (list->head == NULL)
        list->head = list->tail;

    link->state = LL_STATE_LIST;
    return LL_ERR_NONE;
}

/*******************************************************************************
* Reserve and Release
*******************************************************************************/

/**
 * @brief Remove a link from the pool and return pointer to it
 * @param link [out]
 * @param list [in]
 *
 * Using a wrapper function to make returning on error easier
 * with the criticals
 */
int ll_reserve(linked_list_t *list, link_t **link)
{
    CRITICAL(true);
    int status = priv_reserve(list, link);
    CRITICAL(false);
    return status;
}

static int priv_reserve(linked_list_t *list, link_t **link)
{
    PARAM_CHECK (list == NULL);
    PARAM_CHECK (link == NULL);

    int index;
    for (index = 0; index < list->poolSize; index++)
    {
        if (list->pool[index]->state == LL_STATE_POOL)
            break;
    }
    if (index >= list->poolSize) {
        *link = NULL;
        return LL_ERR_MEM;
    }

    *link = list->pool[index];
    (*link)->state = LL_STATE_RESERVED;

    /* Set the pointer to the second item in the list */
    (*link)->after = NULL;
    (*link)->before = NULL;

    return LL_ERR_NONE;
}

/**
 * @brief Reserve a link with a minimum amount of data.
 */
int ll_reserveN(linked_list_t *list, link_t **link, size_t size)
{
    return LL_ERR_NOT_IMPL;
}

int ll_release(linked_list_t *list, link_t *link)
{
    CRITICAL(true);
    int status = priv_release(list, link);
    CRITICAL(false);
    return status;
}
/**
 * @brief Restore ONLY a reserved link to the pool.
 */
static int priv_release(linked_list_t *list, link_t *link)
{
    PARAM_CHECK(list == NULL);
    PARAM_CHECK(link == NULL);
    PARAM_CHECK(link->state != LL_STATE_RESERVED);

    for (int i = 0; i < list->poolSize; i++)
    {
        /* match the pointers */
        if (list->pool[i] == link)
        {
            list->pool[i]->state = LL_STATE_POOL;
            return LL_ERR_NONE;
        }
    }
    return LL_ERR_FAILED;
}



