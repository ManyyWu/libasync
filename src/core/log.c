#include "core/log.h"
#include <stdio.h>

static as_log_cb s_log_cb = as__default_log_callback;

void
as__default_log_callback (int level, const char* file, const char* func,
                          size_t line, const char* format, va_list vl) {
  switch (level) {
  case AS_LOG_FATAL:
  case AS_LOG_ERROR:
  case AS_LOG_WARNING:
    vfprintf(stderr, format, vl);
    break;
  case AS_LOG_INFO:
  case AS_LOG_DEBUG:
  case AS_LOG_TRACE:
    vfprintf(stdout, format, vl);
      break;
  default:
    break;
  }
}

void
as_set_log_callback (as_log_cb cb) {
  s_log_cb = cb ? cb : as__default_log_callback;
}

as_log_cb
as_get_log_callback () {
  return s_log_cb;
}

void
as_log (int level, const char* file, const char* func,
        size_t line, const char* format, ...) {
  va_list vl;

  va_start(vl, format);
  s_log_cb(level, file, func, line, format, vl);
  va_end(vl);
}