#ifndef ASYNC_EPOLL_H
#define ASYNC_EPOLL_H

#include "async.h"
#include "core/list.h"

#include <assert.h>

void
as__io_register (as_loop_t *loop, as__io_t *io, int event);

int
as__io_unregister (as_loop_t *loop, as__io_t *io);

#endif
