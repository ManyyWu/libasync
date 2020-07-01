#include "core/core.h"
#if defined(AS_SYSTEM_WIN32)
#include "win_core.h"
#endif

#include <assert.h>
#include <stdlib.h>

#define DEFAULT_TIMEOUT 3000

static int
as__loop_alive (as_loop_t *loop) {

}

static void
as__update_time (as_loop_t *loop) {
  loop->cached_time = as_monotonic_time(1);
}

static as_ms_t
as__next_timeout (as_loop_t *loop) {
  struct heap_node *min;
  as_timer_t *timer;
  as_ms_t diff;

  /* handleq */
  /* idle */

  if ((min = heap_min(&loop->timer_heap))) {
    timer = container_of((void *)min, as_timer_t, heap_node);
    diff = loop->cached_time - timer->timeout;
    if (diff >= 0)
      return 0;
    return diff;
  }
  return DEFAULT_TIMEOUT;
}

int
as_run (as_loop_t *loop) {
  as_ms_t timeout;
  as__check_param(loop);

  while (!(loop->flags & AS_LOOP_FLAG_STOP) &&
         as__loop_alive(loop)) {
    as__update_time(loop);

   timeout = as__next_timeout(loop);
    as__io_poll(loop, timeout);

    as__update_time(loop);
  }
}

int
as_close (as_handle_t *handle, as_close_cb cb) {
  if (!handle || as__handle_closing(handle))
    return AS_EINVAL;

  if (!(handle->flags & AS_HANDLE_FLAG_NO_CLOSE_CB))
    handle->callback.close_cb = cb;

  // switch

  handle->flags |= AS_HANDLE_FLAG_CLOSING;
}

int
as__io_poll (as_loop_t *loop, as_ms_t timeout) {

}

void
as_once (as_once_t *once, void (*callback)(void)) {
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
