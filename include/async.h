#ifndef ASYNC_H
#define ASYNC_H

#if defined(_cplusplus)
//extern "C" {
#endif

#if defined(AS_BUILDING_SHARED) && defined(AS_USING_SHARED)
#error "Define either AS_BUILDING_SHARED or AS_USING_SHARED, not both."
#endif

#if defined(_WIN32)
# define AS_SYSTEM_WIN32
# if defined(_WIN64)
#   define AS_SYSTEM_WIN64
# endif
#elif defined(__linux__)
# define AS_SYSTEM_LINUX
//#elif defined(__unix__)
//# define AS_SYSTEM_UNIX
#elif defined(__APPLE__) && defined(__MACH__)
# define AS_SYSTEM_DARWIN
#else
# error unsupported platform
#endif

#if defined(_WIN32)
/* Windows - set up dll import/export decorators. */
# if defined(AS_BUILDING_SHARED)
    /* Building shared library. */
#   define AS_EXPORT __declspec(dllexport)
# elif defined(AS_USING_SHARED)
    /* Using shared library. */
#   define AS_EXPORT __declspec(dllimport)
# else
    /* Building static library. */
#   define AS_EXPORT
# endif
#elif __GNUC__ >= 4
# define AS_EXPORT __attribute__((visibility("default")))
#else
# define AS_EXPORT
#endif

#ifdef __GNUC__
#define AS_INLINE static __inline__
#else
#define AS_INLINE static inline
#endif

#include "async/common.h"
#include "async/config.h"
#include "async/error.h"

#if defined(AS_SYSTEM_WIN32)
# include "async/win.h"
#else
# include "async/unix.h"
#endif

#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <stdarg.h>

/* handle types */
typedef struct as_timer_s as_timer_t;

/* request types */

/* callback */
typedef void (*as_log_cb) (int level, const char* file, const char* func,
                           size_t line, const char* format, va_list vl);
typedef void (*as_thread_entry_cb) (void* args);
typedef void (*as_timer_cb) (as_timer_t* handle);

/* error */
AS_EXPORT const char *
as_strerror (int code);

/* time */
typedef uint64_t as_time_t;
typedef as_time_t as_ns_t;
typedef as_time_t as_us_t;
typedef as_time_t as_ms_t;

AS_EXPORT as_ns_t
as_monotonic_time (int fast);
AS_EXPORT as_us_t
as_system_time (void);

/* log */
enum {
  AS_LOG_FATAL   = 1,
  AS_LOG_ERROR   = 2,
  AS_LOG_WARNING = 3,
  AS_LOG_INFO    = 4,
  AS_LOG_DEBUG   = 5,
  AS_LOG_TRACE   = 6,
};

AS_EXPORT void
as_set_log_callback (as_log_cb cb);
AS_EXPORT as_log_cb
as_get_log_callback ();
AS_EXPORT void
as_log (int level, const char* file, const char* func,
        size_t line, const char* format, ...);

/* mutex */
AS_EXPORT int
as_mutex_init (as_mutex_t* mutex);
AS_EXPORT int
as_recursive_mutex_init (as_mutex_t* mutex);
AS_EXPORT void
as_mutex_destroy (as_mutex_t* mutex);
AS_EXPORT void
as_mutex_lock (as_mutex_t* mutex);
AS_EXPORT void
as_mutex_unlock (as_mutex_t* mutex);
AS_EXPORT int
as_mutex_trylock (as_mutex_t* mutex);

/* rwlock */
AS_EXPORT int
as_rwlock_init (as_rwlock_t* rwlock);
AS_EXPORT void
as_rwlock_destroy (as_rwlock_t* rwlock);
AS_EXPORT void
as_rwlock_rdlock (as_rwlock_t* rwlock);
AS_EXPORT void
as_rwlock_rdunlock (as_rwlock_t* rwlock);
AS_EXPORT int
as_rwlock_rdtrylock (as_rwlock_t* rwlock);
AS_EXPORT void
as_rwlock_wrlock (as_rwlock_t* rwlock);
AS_EXPORT void
as_rwlock_wrunlock (as_rwlock_t* rwlock);
AS_EXPORT int
as_rwlock_wrtrylock (as_rwlock_t* rwlock);

/* condition variable */
AS_EXPORT int
as_cond_init (as_cond_t* cond);
AS_EXPORT void
as_cond_destroy (as_cond_t* cond);
AS_EXPORT void
as_cond_signal (as_cond_t* cond);
AS_EXPORT void
as_cond_broadcast (as_cond_t* cond);
AS_EXPORT void
as_cond_wait (as_cond_t* cond, as_mutex_t* mutex);
AS_EXPORT int
as_cond_timedwait (as_cond_t* cond, as_mutex_t* mutex, as_ns_t timeout);

/* barrier */
AS_EXPORT int
as_barrier_init (as_barrier_t* barrier, uint32_t count);
AS_EXPORT void
as_barrier_destroy (as_barrier_t* barrier);
AS_EXPORT void
as_barrier_wait_and_destroy (as_barrier_t* barrier);
AS_EXPORT int
as_barrier_wait (as_barrier_t* barrier);

/* semaphone */
AS_EXPORT int
as_sem_init (as_sem_t* sem, unsigned int value);
AS_EXPORT void
as_sem_destroy (as_sem_t* sem);
AS_EXPORT void
as_sem_post (as_sem_t* sem);
AS_EXPORT void
as_sem_wait (as_sem_t* sem);
AS_EXPORT int
as_sem_trywait (as_sem_t* sem);

/* thread */
typedef uint64_t as_tid_t;

enum {
  AS_THREAD_FLAG_SET_STACK_SIZE = 0x01,
};

typedef struct as_thread_opts_s {
  int flags;
  size_t stack_size;
} as_thread_opts_t;

AS_EXPORT int
as_thread_create (as_thread_t* t,
                  const as_thread_opts_t* opts,
                  as_thread_entry_cb entry,
                  void* args);
AS_EXPORT as_thread_t
as_thread_self (void);
AS_EXPORT as_tid_t
as_thread_tid (void);
AS_EXPORT int
as_thread_join (const as_thread_t* t);
AS_EXPORT int
as_thread_equal (const as_thread_t* t1, const as_thread_t* t2);
AS_EXPORT int
as_stack_trace (void (*callback) (char*));
AS_EXPORT void
as_sleep (as_ms_t ms);
AS_EXPORT void
as_once (as_once_t* once, void (*callback)(void));

/* list */
typedef struct as_list_head_s {
  struct as_list_head_s* next, *prev;
} as_list_head_t;

/* heap */

/* loop */

/* handle */

/* stream */

/* pipe */

/* tcp */

/* udp */

/* signal */

/* async */

/* process */

/* timer */
struct as_timer_s {
  as_timer_cb timeout_cb;
  as_time_t   timeout;
  int         persist;
};

#if defined(__cplusplus)
//extern }
#endif

#endif
