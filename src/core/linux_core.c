#include "async.h"
#include "core/core.h"

#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>

as_ns_t
as_monotonic_time (int fast) {
  static int fast_clock_id = -1;
  struct timespec ts;

  if (fast_clock_id == -1 && fast) {
    if (0 == clock_getres(CLOCK_MONOTONIC_COARSE, &ts) && ts.tv_nsec <= 1e6)
      fast_clock_id = CLOCK_MONOTONIC_COARSE;
    else
      fast_clock_id = CLOCK_MONOTONIC;
  }
  if (clock_gettime((fast ? fast_clock_id : CLOCK_MONOTONIC), &ts))
    abort();
  return AS_TIMESPEC_TO_NS(ts);
}

as_us_t
as_system_time () {
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    abort();

  return AS_TIMEVAL_TO_US(tv);
}