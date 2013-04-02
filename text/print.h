#pragma once

#include <string.h>
#include <stdarg.h>


int el_printInit(void *printFunction);
int el_print(const void *format, ...);
