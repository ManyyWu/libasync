#include "core/core.h"

#include <assert.h>
#include <stdlib.h>

void
as_once (as_once_t* once, void (*callback)(void)) {
  if (pthread_once(once, callback))
    abort();
}

const char *
as_strerror (int code) {
  switch (code) {
#define AS_STRERROR_GEN(code, str) case AS_##code: return str;
    AS_ERRNO_MAP(AS_STRERROR_GEN)
#undef AS_STRERROR_GEN
  default: break;
  }
  return "unknown error";
}

void
as_sleep (as_ms_t ms) {
  int err;
  struct timespec ts;

  AS_MS_TO_TIMESPEC(ts, ms);
  while ((err = nanosleep(&ts, &ts)) < 0 && EINTR == errno)
    ;

  assert(0 == err);
}
