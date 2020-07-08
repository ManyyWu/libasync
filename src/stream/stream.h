#ifndef ASYNC_STREAM_H
#define ASYNC_STREAM_H

#include "async.h"

/* stream */
int
as_stream_init (as_loop_t loop, as_stream_t *stream);

int
as_stream_read_start (as_stream_t *stream);

int
as_stream_read_stop (as_stream_t *stream);

int
as_stream_close (as_stream_t *stream);

#endif
