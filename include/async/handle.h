#ifndef ASYNC_HANDLE_H
#define ASYNC_HANDLE_H

enum {
  AS_HANDLE_FLAG_REF         = 0x0001,
  AS_HANDLE_FLAG_ACTIVED     = 0x0002,
  AS_HANDLE_FLAG_CLOSING     = 0x0003,
  AS_HANDLE_FLAG_CLOSED      = 0x0004,
  AS_HANDLE_FLAG_NO_CLOSE_CB = 0x0005,
};

enum {
  AS_LOOP_FLAG_STOP          = 0x0001,
};

#define AS_HANDLE_MAP(XX) \
    XX(TIMER, timer)      \

#define AS_LOOP_PRIVATE_FIELDS   \
  as_ms_t      cached_time;      \
  as_heap_t    timer_heap;       \
  void        *handleq[2];       \
  uint32_t     actived_handles;  \
  uint32_t     actived_reqs;     \
  uint64_t     flags;            \
  AS_LOOOP_PRIVATE_FIELDS

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

#endif