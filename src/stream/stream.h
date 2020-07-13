#ifndef ASYNC_STREAM_H
#define ASYNC_STREAM_H

#include "async.h"

/* stream */
int
as__stream_init (as_loop_t *loop, as_stream_t *stream);

int
as__stream_read_start (as_stream_t *stream);

int
as__stream_read_stop (as_stream_t *stream);

int
as__stream_close (as_stream_t *stream);

int
as__stream_open (as_stream_t *stream, int fd);

#endif
