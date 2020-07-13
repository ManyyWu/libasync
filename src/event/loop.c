#include "event/win.h"
#include "core/core.h"

#define DEFAULT_TIMEOUT 3000

static as_loop_t *s_default_loop = NULL;

static as_ms_t
as__next_timeout (as_loop_t *loop) {
  struct heap_node *min;
  as_timer_t *timer;

  /* idle */

  min = heap_min(&loop->timer_heap);
  if (min) {
    timer = container_of((void *)min, as_timer_t, heap_node);
    return (timer->timeout >= loop->cached_time ? timer->timeout - loop->cached_time : 0);
  }
  return DEFAULT_TIMEOUT;
}

int
as_loop_init (as_loop_t *loop) {
  int err;

  memset((void *)loop + DATA_OFFSET, 0, sizeof(as_loop_t) - DATA_OFFSET);
  loop->epoll_fd = -1;
  as__timer_heap_init(&loop->timer_heap);
  INIT_LIST_HEAD((struct list_head *)loop->handleq);
  INIT_LIST_HEAD((struct list_head *)loop->requestq);
  INIT_LIST_HEAD((struct list_head *)loop->pending_ioq);
  INIT_LIST_HEAD((struct list_head *)loop->update_ioq);

  err = as__loop_init_platform(loop);
  if (err)
    goto platform_init_fail;

  as_update_time(loop);

  return 0;
  platform_init_fail:
  as__loop_close_platform(loop);
  return err;
}

as_loop_t *
as_default_loop () {
  if (!s_default_loop) {
    s_default_loop = as_malloc(sizeof(as_loop_t));
    if (!s_default_loop)
      return NULL;
    as_loop_init(s_default_loop);
  }

  return s_default_loop;
}

int
as_loop_close (as_loop_t *loop) {
  struct list_head *pos, *next;
  if (!loop)
    return AS_EINVAL;

  /* unregister io */
  /* close fd */
  /* close timers */

  list_for_each_safe(pos, next, (struct list_head *)loop->handleq)
  list_del_init(pos);
  list_for_each_safe(pos, next, (struct list_head *)loop->requestq)
  list_del_init(pos);
  list_for_each_safe(pos, next, (struct list_head *)loop->pending_ioq)
  list_del_init(pos);
  list_for_each_safe(pos, next, (struct list_head *)loop->update_ioq)
  list_del_init(pos);

  as__loop_close_platform(loop);

  if (loop == s_default_loop) {
    as_free(loop);
    s_default_loop = NULL;
  }

  return 0;
}

int
as_run (as_loop_t *loop) {
  as_ms_t timeout;

  while (!(loop->flags & AS_LOOP_FLAG_STOP) && as__loop_alive(loop)) {
    as_update_time(loop);

    timeout = as__next_timeout(loop);
    as__io_poll(loop, timeout);

    as_update_time(loop);
    as__process_timers(loop);
  }
}

int
as_close (as_handle_t *handle, as_close_cb cb) {
  int err;

  if (!handle || as__handle_closing(handle))
    return AS_EINVAL;

  if (!(handle->flags & AS_HANDLE_FLAG_NO_CLOSE_CB))
    handle->callback.close_cb = cb;

  switch (handle->type) {
#define AS_HANDLE_CLOSE_GEN(type, name)                   \
  case AS_HANDLE_TYPE_##type:                             \
    err = as__##name##_close ((as_##name##_t *)(handle)); \
    break;

    AS_HANDLE_TYPE_MAP(AS_HANDLE_CLOSE_GEN)

#undef AS_HANDLE_CLOSE_GEN
    default:
      return AS_EINVAL;
  }

  handle->flags |= AS_HANDLE_FLAG_CLOSING;
  if (handle->flags & AS_HANDLE_FLAG_NO_CLOSE_CB)
    handle->flags |= AS_HANDLE_FLAG_CLOSED;

  return err;
}

int
as__loop_alive (as_loop_t *loop) {
  if (loop->actived_handles)
    return 1;
  if (loop->actived_reqs)
    return 1;

  return 0;
}

void
as_update_time (as_loop_t *loop) {
  loop->cached_time = as_monotonic_time(1) / AS_USEC;
}

static void
as__set_no_close_cb (as_handle_t *handle) {
  switch (handle->type) {
    case AS_HANDLE_TYPE_TIMER:
      handle->flags |= AS_HANDLE_FLAG_NO_CLOSE_CB;
      break;
    default:
      break;
  }
}

int
as__handle_init (as_loop_t *loop, as_handle_t *handle, int type) {
  if (as__handle_has_ref((handle)))
    return AS_EINVAL;

  /* you have to call memset and then call as__handle_init */
  handle->loop = loop;
  handle->type = type;
  as__set_no_close_cb(handle);
  as__handleq_add(loop, handle);

  return 0;
}

int
as__handle_close (as_handle_t *handle) {
  if (!as__handle_has_ref((handle)))
    return AS_EINVAL;

  as__handleq_del(handle->loop, handle);
  handle->loop = NULL;

  return 0;
}

int
as_closed (as_handle_t *handle) {
  return (0 != (handle->flags & AS_HANDLE_FLAG_CLOSED));
}

int
as_closing (as_handle_t *handle) {
  return (0 != (handle->flags & AS_HANDLE_FLAG_CLOSING));
}
