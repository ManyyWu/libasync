#ifndef ASYNC_EPOLL_H
#define ASYNC_EPOLL_H

#include "async.h"

void
as__io_register (as__io_t *io, int event);

void
as__io_unregister (as__io_t *io, int event);

#endif
