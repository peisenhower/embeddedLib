


#pragma once

#ifndef ATTR_INLINE
#   if  __ICCARM__
#       define ATTR_INLINE 
#   else
#       define ATTR_INLINE __attribute__ ((always_inline))
#   endif
#endif 

#ifndef UNUSED
#    define UNUSED(x) x __attribute__((unused))
#endif
