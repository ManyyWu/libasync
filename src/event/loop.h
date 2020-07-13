#ifndef ASYNC_LOOP_H
#define ASYNC_LOOP_H

#include "async.h"

#define DATA_OFFSET (sizeof(void *))

/* loop */
int
as__loop_init_platform (as_loop_t *loop);

void
as__loop_close_platform (as_loop_t *loop);

int
as__loop_alive (as_loop_t *loop);

/* event process */
void
as__process_event (as_loop_t *loop, as__io_t *io, unsigned int events);

void
as__process_timers (as_loop_t *loop);

/* io watcher */
void
as__io_init (as__io_t *io, int fd);

void
as__io_close (as__io_t *io);

int
as__io_poll (as_loop_t *loop, as_ms_t timeout);

/* handle */
int
as__handle_init (as_loop_t *loop, as_handle_t *handle);

int
as__handle_close (as_handle_t *handle);

/* timer */
void
as__timer_heap_init (as_heap_t *heap);

int
as__timer_close (as_timer_t *timer);

#endif