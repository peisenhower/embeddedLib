/*************************************************************************
 * Includes 
 *************************************************************************/
#include <stdio.h>
#include "linked-list.h"
#include "common.h"

/*************************************************************************
 * Local Defines
 *************************************************************************/
#define COUNTOF(arr) (sizeof(arr) / sizeof(arr[0]))

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
    linked_list_t list;

    for (int i = 0; i < COUNTOF(links); i++)
    {
        links[i].data = dataStore[i];
        links[i].size = sizeof(dataStore[i]);
    }

    ll_create(&list, links, COUNTOF(links), myCrit);

    return 0;
}


static void myCrit(bool enable)
{
    if (previousCrit == enable)
        printf("Critical section was escaped with out being disabled\n");

    previousCrit = enable;
}



