/*************************************************************************
 * Includes 
 *************************************************************************/
#include <stdio.h>
#include "circular-buffer.h"

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
static int print_cb(cb_t *cb);

/*************************************************************************
 * Static Variables 
 *************************************************************************/

/*************************************************************************
 * Functions
 *************************************************************************/


int main(int argc, const char *argv[])
{
    printf("%s\r\n", "Circular Buffer, Build: " __DATE__ "  " __TIME__  );

    cb_t cb;
    uint8_t     buf[123];

    printf("CB Before Init\r\n");
    print_cb(&cb);

    cb_init(&cb, buf, sizeof(buf));

    printf("CB After Init\r\n");
    print_cb(&cb);


    return 0;
}



static int print_cb(cb_t *cb)
{
    printf("RI: %5lu   WI: %5lu   Size: %5lu   Lock: %d\r\n", 
            cb->read_index, 
            cb->write_index, 
            cb->buffer_size, 
            cb->lock);

    return 0;
}


