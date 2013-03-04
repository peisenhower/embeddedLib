

#ifndef COUNTOF
#define COUNTOF(x) (sizeof(x) / sizeof(x[0])
#endif

#define RETURN_ERR_IF(x)        \
        do {                    \
            if(x) {             \
                /* print something */   \
                return -1;      \
            }}while(0);
