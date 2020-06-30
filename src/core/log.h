#ifndef ASYNC_LOG_H
#define ASYNC_LOG_H

#include "async.h"

void
as__default_log_callback (int level, const char *file, const char *func,
                          size_t line, const char *format, va_list vl);

#endif