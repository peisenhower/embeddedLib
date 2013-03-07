


#pragma once

#ifndef ATTR_INLINE
#    define ATTR_INLINE __attribute__ ((always_inline))
#endif 

#ifndef UNUSED
#    define UNUSED(x) x __attribute__((unused))
#endif
