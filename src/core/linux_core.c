#include "async.h"
#include "core/core.h"
#if defined(AS_SYSTEM_WIN32)
#include "win_core.h"
#endif

#include <stdlib.h>
#include <execinfo.h>
#include <sys/time.h>
#include <unistd.h>

#define STACK_TRACE_LINE 128

as_ns_t
as_monotonic_time (int fast) {
  static int fast_clock_id = -1;
  struct timespec ts;

  if (fast_clock_id == -1 && fast) {
#if defined(CLOCK_MONOTONIC_COARSE)
    if (!clock_getres(CLOCK_MONOTONIC_COARSE, &ts) && ts.tv_nsec <= 1e6)
      fast_clock_id = CLOCK_MONOTONIC_COARSE;
    else
#endif
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

int
as_stack_trace (void (*callback) (char*)) {
  void *array[STACK_TRACE_LINE];
  char **stacks;
  int line;
  int i;

  if (!callback)
    return AS_EINVAL;

  line = backtrace(array, STACK_TRACE_LINE);
  if (line <= 0)
    return AS_ENOMEM;

  stacks = backtrace_symbols(array, line);
  if (!stacks)
    return AS_ENOMEM;

  for (i = 0; i < line; ++i)
    callback(stacks[i]);

  free(stacks);

  return line;
}
