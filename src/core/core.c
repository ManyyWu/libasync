#include "core/core.h"

#include <assert.h>

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
