#include "async.h"
#include "core/core.h"

#include <assert.h>

static int
timer_less_than (const void *a, const void *b) {
  as_ms_t ta, tb;

  assert(a && b);

  ta = container_of(a, as_timer_t, heap_node)->timeout;
  tb = container_of(b, as_timer_t, heap_node)->timeout;

  return (ta < tb);
}

int
as_update_time (as_loop_t *loop) {
  as__update_time(loop);
}

int
as_timer_init (as_loop_t *loop, as_timer_t *handle) {
  int err;

  memset((void *)handle + DATA_OFFSET, 0, sizeof(as_timer_t) - DATA_OFFSET);
  err = as__handle_init(loop, (as_handle_t *)handle);
  if (err)
    return err;

  handle->timeout = 0;
  handle->interval = 0;
  handle->timeout_cb = NULL;

  return 0;
}

int
as_timer_start (as_timer_t *handle, as_ms_t timeout, as_ms_t interval, as_timer_cb cb) {
  as_loop_t *loop;

  if (!cb)
    return AS_EINVAL;
  if (!as__handle_has_ref(handle) || as__handle_closing(handle))
    return AS_EINVAL;
  if (as__handle_has_active(handle))
    as_timer_stop(handle);

  loop = handle->loop;
  handle->timeout = loop->cached_time + timeout;
  handle->interval = interval;
  handle->timeout_cb = cb;

  heap_insert(&loop->timer_heap, (struct heap_node *)handle->heap_node);
  as__handle_start(loop, handle);

  return 0;
}

int
as_timer_stop (as_timer_t *handle) {
  as_loop_t *loop;

  if (!as__handle_has_active(handle))
    return AS_EINVAL;

  handle->timeout_cb = NULL;

  loop = handle->loop;
  heap_remove(&loop->timer_heap, (struct heap_node *)handle->heap_node);
  as__handle_stop(loop, handle);

  return 0;
}

int
as_timer_expired (as_timer_t *handle) {
  return (!handle->timeout_cb);
}

void
as__process_timers (as_loop_t *loop) {
  struct heap_node *min;
  as_timer_t *timer;
  as_ms_t interval;
  as_timer_cb cb;

  while ((min = heap_min(&loop->timer_heap))) {
    timer = container_of((void *)min, as_timer_t, heap_node);
    interval = timer->interval;
    cb = timer->timeout_cb;
    assert(cb);

    if (loop->cached_time < timer->timeout)
      break;

    timer->timeout_cb = NULL; /* expired */
    cb(timer);

    if (as__handle_has_active(timer) && !timer->timeout_cb) {
      as_timer_stop(timer);
      if (timer->interval)
        as_timer_start(timer, interval, interval, cb);
    }
  }
}

void
as__timer_heap_init (as_heap_t *heap) {
  heap_init(heap, timer_less_than);
}

