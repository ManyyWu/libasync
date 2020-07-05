#ifndef ASYNC_CORE_H
#define ASYNC_CORE_H

#include "async.h"
#include "core/list.h"
#include "core/heap.h"
#include "core/common_internal.h"

#include <memory.h>

#if !defined(NDEBUG)
# include <stdio.h>
#endif

#define DATA_OFFSET (sizeof(void *))

int
as__loop_init_platform (as_loop_t *loop);

void
as__loop_close_platform (as_loop_t *loop);

void
as__io_init (as__io_t *io, int fd);

int
as__io_poll (as_loop_t *loop, as_ms_t timeout);

int
as__handle_init (as_loop_t *loop, as_handle_t *handle);

int
as__handle_close (as_handle_t *handle);

int
as__loop_alive (as_loop_t *loop);

void
as__update_time (as_loop_t *loop);

void
as__process_event (as_loop_t *loop, as__io_t *io, unsigned int events);

void
as__process_timers (as_loop_t *loop);

void
as__timer_heap_init (as_heap_t *heap);

int
as__timer_close (as_timer_t *timer);

#endif