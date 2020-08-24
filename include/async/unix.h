#ifndef ASYNC_UNIX_H
#define ASYNC_UNIX_H

#include <sys/types.h>

#include <semaphore.h>
#include <pthread.h>

#include <netdb.h>

#if defined(AS_SYSTEM_LINUX)
# include "sys/epoll.h"
#elif defined(AS_SYSTEM_DARWIN)
# include "async/darwin.h"
#endif

#define AS_HANDLE_PLATFORM_FIELDS /* empty */

#define AS_LOOOP_PLATFORM_FIELDS /* empty */

#define AS_STREAM_PLATFORM_FIELDS     \
  union {                             \
    struct {                          \
      as_connect_req *connect_req;    \
      as_read_cb      read_cb;        \
      void           *write_reqs[2];  \
      void           *writed_reqs[2]; \
      size_t          writeq_bytes;   \
    } session;                        \
    struct {                          \
      as_session_cb  *session_cb;     \
      int             accept_fd;      \
      int            *accept_fds;     \
    } server;                         \
  } s;

#if defined(AS_SYSTEM_DARWIN)
typedef semaphone_t as_platform_sem_t;
#else
typedef sem_t as_platform_sem_t;
#endif

typedef pthread_mutex_t as_mutex_t;
typedef pthread_rwlock_t as_rwlock_t;
typedef pthread_cond_t as_cond_t;
typedef pthread_barrier_t as_barrier_t;
typedef as_platform_sem_t as_sem_t;
typedef pthread_t as_thread_t;
typedef pthread_once_t as_once_t;

#if defined(AS_SYSTEM_LINUX)
#define AS__IO_PLATFORM_FIELDS \
   unsigned int mod_events;    \
   unsigned int events;

#elif defined(AS_SYSTEM_DARWIN)
#endif

#endif
