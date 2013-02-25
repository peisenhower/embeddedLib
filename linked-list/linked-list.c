 /*************************************************************************
  * Includes 
  *************************************************************************/
#include "linked-list.h"
 
 /*************************************************************************
  * Local Defines
  *************************************************************************/
 
 /*************************************************************************
  * Local Types and Typedefs
  *************************************************************************/
 
 /*************************************************************************
  * Global Variables
  *************************************************************************/
 
 /*************************************************************************
  * Static Function Prototypes
  *************************************************************************/
static int priv_poolRemove(const linked_list_t *list, link_t **link);
static int priv_poolAdd(linked_list_t *list, link_t *add);
 
 /*************************************************************************
  * Static Variables 
  *************************************************************************/
 
 /*************************************************************************
  * Functions
  *************************************************************************/


int ll_create(linked_list_t *list, link_t *links[], size_t linksCount)
{

    if (list == NULL)
        return EL_ERR_PARAM; 
    if (links == NULL) 
        return EL_ERR_PARAM; 
    if (length == 0)
        return EL_ERR_PARAM; 

    list->head = NULL; 
    list->tail = NULL; 
    list->pool = links; 
    list->poolSize = linksCount;  

    return EL_ERR_NONE;
}

int ll_addHead(linked_list_t *list, void *data, size_t size)
{
    if (list == NULL)
        return EL_ERR_PARAM; 
    if (data == NULL) 
        return EL_ERR_PARAM; 
    if (list->poolSize == 0)
        return EL_ERR_MEM; 

    link_t *link; 
    int result = priv_poolRemove(list, &link); 

    if (result) 
        return result; 

    list->head = link; 


    return EL_ERR_NONE;
}

int ll_addTail()
{

}


int ll_addBefore()
{
}

int ll_addAfter()
{

}

int ll_removeHead()
{
}
int ll_removeTail()
{
}

int ll_removeAt()
{
}


/**
 * Remove a link from the pool to add to the linked list. 
 */
static int priv_poolRemove(const linked_list_t *list, link_t **link)
{
    for (int i = 0; i < list->poolSize; i++) 
    {
        if (list->pool[i].flags & LL_FLAG_POOL) 
        {
            **link = list->pool[i];
            list->pool[i].flags &= ~LL_FLAG_POOL; 
            list->poolSize -= 1;
            return EL_ERR_NONE; 
        }
    }
    return EL_ERR_MEM; 
}

/** 
 * Restore a link back to the pool. 
 */
static int priv_poolAdd(linked_list_t *list, link_t *add)
{
    for (int i = 0; i < list->poolSize; i++) 
    {
        /* match the pointers */ 
        if (&list->pool[i] == add) 
        {
            list->pool[i].flags |= LL_FLAG_POOL; 
            list->poolSize += 1;
            return EL_ERR_NONE; 
        }
    }
    return EL_ERR_FAILED; 
}
