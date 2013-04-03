#pragma once

#include <string.h>
#include <stdarg.h>


typedef int (* print_fn_t) (const void *, size_t);

int el_printInit(print_fn_t printFunction);
int el_print(const void *format, ...);
