/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <string.h>

/*******************************************************************************
* Defines
*******************************************************************************/

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Static Variables
*******************************************************************************/

/*******************************************************************************
* Functions
*******************************************************************************/


uint8_t el_lrc8 (uint8_t initial, const uint8_t *data, size_t length)
{
    uint8_t lrc = initial;

    for (size_t i = 0; i < length; i++) {
        lrc ^= data[i];
    }
    return lrc;
}
