#include <stdint.h>
#include <string.h>

/* Addapted from wikipedia */
uint16_t el_fletcher16( uint8_t *data, size_t length) 
{
    uint16_t sum1 = 0xff, sum2 = 0xff;

    while (length) {
        size_t tlen = length > 20 ? 20 : length;
        length -= tlen;
        do {
            sum2 += sum1 += *data++;
        } while (--tlen);
        sum1 = (sum1 & 0xff) + (sum1 >> 8);
        sum2 = (sum2 & 0xff) + (sum2 >> 8);
    }
    /* Second reduction step to reduce sums to 8 bits */
    sum1 = (sum1 & 0xff) + (sum1 >> 8);
    sum2 = (sum2 & 0xff) + (sum2 >> 8);
    return sum2 << 8 | sum1;
}

uint32_t el_fletcher32(const uint8_t *data, size_t length)
{
    uint32_t sum1 = 0xffff, sum2 = 0xffff;

    while (length)
    {
        size_t tlen = length > 359 ? 359 : length;
        length -= tlen;
        do {
            sum2 += sum1 += *data++;
        } while (--tlen);
        sum1 = (sum1 & 0xffff) + (sum1 >> 16);
        sum2 = (sum2 & 0xffff) + (sum2 >> 16);
    }
    /* Second reduction step to reduce sums to 16 bits */
    sum1 = (sum1 & 0xffff) + (sum1 >> 16);
    sum2 = (sum2 & 0xffff) + (sum2 >> 16);
    return sum2 << 16 | sum1;
}


