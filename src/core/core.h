#ifndef ASYNC_CORE_H
#define ASYNC_CORE_H

#include "async.h"
#include "core/list.h"
#include "core/heap.h"
#include "core/common_internal.h"

void
as__process_timers (as_loop_t *loop);

int
as__io_poll (as_loop_t *loop, as_ms_t timeout);

#endif