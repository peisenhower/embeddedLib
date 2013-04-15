/*************************************************************************
 * Includes 
 *************************************************************************/
#include <stdio.h>
#include "linked-list.h"
#include "common.h"

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
static void myCrit(bool enable);
static void printList(linked_list_t *list);
static void printLink(link_t *link);

/*************************************************************************
 * Static Variables 
 *************************************************************************/
static bool previousCrit = false;

/*************************************************************************
 * Functions
 *************************************************************************/


int main(int argc, const char *argv[])
{
    uint8_t dataStore[8][128];
    link_t links[8];
    link_t *table[8];
    linked_list_t list;

    for (int i = 0; i < COUNTOF(links); i++)
    {
        links[i].data = dataStore[i];
        links[i].size = sizeof(dataStore[i]);
        table[i] = &links[i];
    }

    int status = ll_create(&list, table, COUNTOF(links), myCrit);
    printf("Create Result: %d\n", status);
    printList(&list);

    link_t *firstLink;
    status = ll_reserve(&list, &firstLink);
    printf("Reserve Result: %d\n", status);
    printLink(firstLink);
    for ( int i = 0; i < firstLink->size; i++)
        firstLink->data[i] = i;

    status = ll_pushHead(&list, firstLink);
    printf("Push Head Result: %d\n", status);
    printList(&list);


    link_t *shouldBeFirst;
    status = ll_pullHead(&list, &shouldBeFirst);
    printf("Pull Head Result: %d\n", status);
    printLink(shouldBeFirst);
    printList(&list);
    if (shouldBeFirst != firstLink)
        printf("pushed link did not match pulled one\n");

    return 0;
}


static void myCrit(bool enable)
{
    if (previousCrit == enable)
        printf("Critical section was escaped with out being disabled\n");

    previousCrit = enable;
}

static void printList(linked_list_t *list)
{
    printf("Head: %08x\n",(unsigned int) list->head);
    printf("Tail: %08x\n",(unsigned int) list->tail);
}

static void printLink(link_t *link)
{
    printf("Before: %08x\n",(unsigned int) link->before);
    printf("After: %08x\n",(unsigned int) link->after);
    printf("State: %08x\n",(unsigned int) link->state);
    printf("flags: %08x\n",(unsigned int) link->flags);
    printf("size: %08x\n",(unsigned int) link->size);
}
