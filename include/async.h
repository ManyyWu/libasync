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

/* constants */
#define AS_NSEC (uint64_t)1e9
#define AS_USEC (uint64_t)1e6
#define AS_MSEC (uint64_t)1e3

/* macros */
#define AS_TIMESPEC_TO_NS(ts)                                                               \
    ((ts).tv_sec*AS_NSEC + (ts).tv_nsec)
#define AS_TIMESPEC_TO_US(ts)                                                               \
    ((ts).tv_sec*AS_USEC + (ts).tv_nsec/AS_MSEC)
#define AS_TIMESPEC_TO_MS(ts)                                                               \
    ((ts).tv_sec*AS_MSEC + (ts).tv_nsec/AS_USEC)
#define AS_NS_TO_TIMESPEC(ts, ns)                                                           \
    do { (ts).tv_sec = (ns)/AS_NSEC; (ts).tv_nsec = (ns)%AS_NSEC; } while (0)
#define AS_US_TO_TIMESPEC(ts, us)                                                           \
    do { (ts).tv_sec = (us)/AS_USEC; (ts).tv_nsec = ((us)%AS_USEC)*AS_MSEC; } while (0)
#define AS_MS_TO_TIMESPEC(ts, ms)                                                           \
    do { (ts).tv_sec = (ms)/AS_MSEC; (ts).tv_nsec = ((ms)%AS_MSEC)*AS_USEC; } while (0)
#define AS_TIMEVAL_TO_US(tv)                                                                \
    ((tv).tv_sec*AS_USEC + (tv).tv_usec)
#define AS_TIMEVAL_TO_MS(tv)                                                                \
    ((tv).tv_sec*AS_MSEC + (tv).tv_usec/AS_MSEC)
#define AS_US_TO_TIMEVAL(tv, us)                                                            \
    do { (tv).tv_sec = (us)/AS_USEC; (tv).tv_usec = (us)%AS_USEC; } while (0)
#define AS_MS_TO_TIMEVAL(tv, ms)                                                            \
    do { (tv).tv_sec = (ms)/AS_MSEC; (tv).tv_usec = ((ms)%AS_MSEC)*AS_MSEC; } while (0)

/* types */

/* error */
AS_EXPORT const char *
as_strerror (int code);

/* time */
typedef uint64_t as_ns_t;
typedef uint64_t as_us_t;
typedef uint64_t as_ms_t;

AS_EXPORT as_ns_t
as_monotonic_time (int fast);
AS_EXPORT as_us_t
as_system_time (void);

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
typedef void (*thread_entry)(void*);

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
                  thread_entry entry,
                  void *args);
AS_EXPORT as_thread_t
as_thread_self (void);
AS_EXPORT as_tid_t
as_thread_tid (void);
AS_EXPORT int
as_thread_join (const as_thread_t* t);
AS_EXPORT int
as_thread_equal (const as_thread_t* t1, const as_thread_t* t2);
AS_EXPORT void
as_stack_trace (char **buf, size_t *size);
AS_EXPORT void
as_sleep (as_ms_t ms);
AS_EXPORT void
as_once (as_once_t* once, void (*callback)(void));

#if defined(__cplusplus)
//extern }
#endif

#endif
