#include "async.h"
#include "core/core.h"
#if defined(AS_SYSTEM_WIN32)
#include "win_core.h"
#endif

#include <stdlib.h>
#include <assert.h>
#include <execinfo.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#define STACK_TRACE_LINE 128
#define EPOLL_EVENTS_MAX 1024

int
as__loop_init_platform (as_loop_t *loop) {
  int fd;

  fd = epoll_create1(O_CLOEXEC);
  if (fd < 0)
    return AS_ERRNO(errno);

  loop->epoll_fd = fd;

  return 0;
}

void
as__loop_close_platform (as_loop_t *loop) {
  if (loop->epoll_fd > 0) {
    close(loop->epoll_fd);
    loop->epoll_fd = -1;
  }
}

void
as__io_init (as__io_t *io, int fd) {
  io->fd = fd;
  io->delayed_errno = 0;
  io->mod_events = 0;
  io->events = 0;
  INIT_LIST_HEAD((struct list_head *)io->update_ioq);
  INIT_LIST_HEAD((struct list_head *)io->pending_ioq);
}

int
as__io_poll (as_loop_t *loop, as_ms_t timeout) {
  struct epoll_event events[EPOLL_EVENTS_MAX];
  struct epoll_event e;
  struct list_head *pos, *next;
  as_ms_t start, diff;
  as__io_t *entry;
  int nevents;
  int err;
  int op;
  int i;

  start = loop->cached_time;

  list_for_each_safe(pos, next, (struct list_head *)loop->update_ioq) {
    entry = list_entry((void *)pos, as__io_t, update_ioq);
    list_del_init(pos);

    assert(entry->fd > 0);
    if (entry->mod_events == entry->events)
      continue;

    op = entry->events ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
    e.data.ptr = entry;
    e.events = entry->mod_events;

    err = epoll_ctl(loop->epoll_fd, op, entry->fd, &e);
    if (err) {
      assert(EEXIST != errno);
      if (EEXIST != errno)
        abort();
      assert(EPOLL_CTL_ADD == op);
      err = epoll_ctl(loop->epoll_fd, EPOLL_CTL_MOD, entry->fd, &e);
      if (err)
        abort();
    }
    entry->events = entry->mod_events;
  }

  while (timeout > 0) {
    nevents = epoll_wait(loop->epoll_fd, events, EPOLL_EVENTS_MAX, timeout);
    if (nevents < 0) {
      if (ENOSYS == errno)
        abort();
      if (EINTR != errno)
        abort();
    }
    as__update_time(loop);
    diff = loop->cached_time - start;
    timeout = diff < timeout ? timeout - diff : 0;

    for (i = 0; i < nevents; ++i) {
      assert(events[i].data.ptr);
      as__process_event(loop, events[i].data.ptr, events[i].events);
    }
  }
}

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
