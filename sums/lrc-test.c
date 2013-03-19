
#include "lrc.h"
#include "common.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    uint8_t data[] = { 1, 2, 3, 4 };

    uint8_t expected = 0xff ^ 1 ^ 2 ^ 3 ^ 4;
    uint8_t actual = el_lrc8(LRC_INITIAL, data, COUNTOF(data));

    if (expected != actual)
        printf("Failed, Expected:%02x Actual:%02x\n", expected, actual);
    else
        printf("Success\n");


    return 0;
}



