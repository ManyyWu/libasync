#include "async.h"
#include "core/core.h"

#include <assert.h>

int
as_timer_init (as_loop_t *loop, as_timer_t *handle) {
  as__check_param(loop && handle);

  as__handle_init(loop, handle);
  handle->timeout = 0;
  handle->interval = 0;
  handle->timeout_cb = NULL;

  return 0;
}

int
as_timer_start (as_timer_t *handle, as_ms_t timeout, as_ms_t interval, as_timer_cb cb) {
  as_loop_t *loop;
  as__check_param(handle && cb);

  if (!as__handle_has_ref(handle))
    return AS_EINVAL;
  if (as__handle_closing(handle))
    return AS_EINVAL;
  if (as__handle_has_active(handle))
    as_timer_stop(handle);

  loop = handle->loop;
  handle->timeout += loop->cached_time;
  handle->interval = interval;
  handle->timeout_cb = cb;

  heap_insert((as_heap_t *)&loop->timer_heap, (struct heap_node *)handle->heap_node);
  as__handle_start(loop, handle);

  return 0;
}

int
as_timer_stop (as_timer_t *handle) {
  as_loop_t *loop;
  as__check_param(handle);

  if (!as__handle_has_active(handle))
    return AS_EINVAL;

  handle->timeout_cb = NULL;

  loop = handle->loop;
  heap_remove((as_heap_t *)&loop->timer_heap, (struct heap_node *)handle->heap_node);
  as__handle_stop(loop, handle);
}

int
as_timer_expired (as_timer_t *handle) {
  return (!handle->timeout_cb);
}

static struct heap_node *
as__timerq_pop_min (as_heap_t *heap) {
  struct heap_node *min;

  min = heap->min;
  if (min)
    heap_pop(heap);

  return min;
}

void
as__process_timers (as_loop_t *loop) {
  as_ms_t now_time;
  as_timer_t *timer;
  struct heap_node *min;

  now_time = loop->cached_time;
  while ((min = as__timerq_pop_min(&loop->timer_heap))) {
    timer = container_of((void *)min, as_timer_t, heap_node);
    if (timer->timeout >= now_time)
      timer->timeout_cb(timer);
    if (!timer->interval)
      as_timer_stop(timer);
  }
}
