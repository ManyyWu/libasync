#include "core/core.h"
#include "event/loop.h"
#include "stream/unix_stream.h"

#include <unistd.h>
#include <assert.h>

int
as__stream_init (as_loop_t *loop, as_stream_t *stream) {
  int err;

  stream->error = 0;
  stream->alloc_cb = NULL;
  as__io_init(&stream->io, -1);

  return 0;
}

int
as__stream_read_start (as_stream_t *stream) {

}

int
as__stream_read_stop (as_stream_t *stream) {
  int err;

  as__io_close(&stream->io);

  return 0;
}

int
as__stream_open (as_stream_t *stream, int fd) {

}

int
as__stream_close (as_stream_t *stream) {

}

