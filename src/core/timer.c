#include "async.h"
#include "core/core.h"
#include "core/heap.h"

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
  as__check_param(handle);

  /*
  loop = handle->loop;
  if (as__handle_closing(handle) || !cb);
    return AS_EINVAL;
  if (as__handle_actived(handle))
    as_timer_stop(handle);

  handle->timeout += loop->cached_time;
  handle->interval = internval;
  handle->timeout_cb = cb;

  heap_insert(&loop->timerq.heap, (struct heap_node *)handle->heap_node);
  */

  return 0;
}

void
as_timer_reset (as_timer_t *handle, as_ms_t timeout, as_ms_t interval, as_timer_cb cb) {

}

int
as_timer_stop (as_timer_t *handle) {

}
