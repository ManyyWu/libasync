#ifndef ASYNC_HANDLE_H
#define ASYNC_HANDLE_H

#if defined(AS_SYSTEM_WIN32)
# include "async/win.h"
#else
# include "async/unix.h"
#endif

enum {
  AS_HANDLE_FLAG_REF         = 0x0001,
  AS_HANDLE_FLAG_ACTIVED     = 0x0002,
  AS_HANDLE_FLAG_CLOSING     = 0x0004,
  AS_HANDLE_FLAG_CLOSED      = 0x0008,
  AS_HANDLE_FLAG_NO_CLOSE_CB = 0x0010,
};

enum {
  AS_LOOP_FLAG_STOP          = 0x0001,
};

#define AS_HANDLE_TYPE_MAP(XX)   \
    XX(TIMER, timer)             \

#define AS_LOOP_PRIVATE_FIELDS   \
  uint64_t     flags;            \
  /* timer */                    \
  as_ms_t      cached_time;      \
  as_heap_t    timer_heap;       \
  /* handles */                  \
  void        *handleq[2];       \
  uint32_t     actived_handles;  \
  /* requests */                 \
  void        *requestq[2];      \
  uint32_t     actived_reqs;     \
  /* reactor */                  \
  as__io_t   **io_list;          \
  uint32_t     io_list_size;     \
  uint32_t     watching_fds;     \
  int          epoll_fd;         \
  void        *pending_ioq[2];   \
  void        *update_ioq[2];    \
  AS_LOOOP_PLATFORM_FIELDS

#define AS_HANDLE_PRIVATE_FIELDS \
  int          flags;            \
  int          type;             \
  void        *handleq_node[2];  \
  as_loop_t   *loop;             \
  union {                        \
    as_close_cb close_cb;        \
    as_timer_cb timer_cb;        \
  } callback;                    \
  AS_HANDLE_PLATFORM_FIELDS

#define AS_TIMER_PRIVATE_FIELDS  \
  as_ms_t     timeout;           \
  as_ms_t     interval;          \
  as_timer_cb timeout_cb;        \
  void       *heap_node[3];

typedef struct as__io_s {
  int   fd;
  int   delayed_errno;
  void *update_ioq[2];
  void *pending_ioq[2];
  AS__IO_PLATFORM_FIELDS
} as__io_t;

#endif