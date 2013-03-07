#include <stdint.h>
#include <string.h>

#define DELIMITER   0x7E
#define ESCAPE      0x7D
#define ESCAPE_7E   0x5D
#define ESCAPE_7D   0x5D


int el_hdlcDecodeSize(uint8_t *in, size_t length, size_t *decodeLength)
{
    size_t i;
    size_t escapes = 0;

    if (in == NULL || decodeLength == NULL) 
        return -1;

    if (in[0] != DELIMITER || in[length - 1] != DELIMITER)
        return -1; /* Malformed HDLC */
    else
        escapes = 2;

    for (i = 1; i < length - 1; i++)
    {
        if (in[i] == ESCAPE)
        {
            i++;
            if (in[i] == ESCAPE_7E || in[i] == ESCAPE_7D)
                escapes++;
            else
                return -1; /* Malformed HDLC */
        }
        else if (in[i] == DELIMITER)
        {
            return -1; /* Malformed HDLC */
        }
    }

    *decodeLength = length - escapes;

    return 0;
}

int el_hdlcEncodeSize(uint8_t *in, size_t length, size_t *encodeLength)
{
    size_t i;
    size_t escapes = 0;

    if (in == NULL || encodeLength == NULL)
        return -1;

    for (i = 0; i < length; i++)
    {
        if ( in[i] == ESCAPE || in[i] == DELIMITER )
            escapes++;
    }

    *encodeLength = length + escapes + 2; /* 2 for Delimiters */

    return 0;
}

int el_hdlcEncode(uint8_t *in, size_t inLength, uint8_t *out, size_t outLength)
{
    size_t i;

    if (in == NULL || out == NULL)
        return -1;

    for (i = 0; i < inLength; i++) 
    {


    }

}

int el_hdlcDecode(uint8_t *in, size_t inLength, uint8_t *out, size_t outLength)
{



}




