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
#elif defined(TARGET_OS_MAC)
# define AS_SYSTEM_MACOS
#elif defined(__linux__)
# define AS_SYSTEM_LINUX
#elif defined(__unix__)
# define AS_SYSTEM_MACOSS
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
#   define AS_EXPORT /* nothing */
# endif
#elif __GNUC__ >= 4
# define AS_EXPORT __attribute__((visibility("default")))
#else
# define AS_EXPORT /* nothing */
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

/* constants */

/* macro */
#define AS_TIMESPEC_TO_NS(ts) ((ts).tv_sec*(as_ns_t)1e9 + (ts).tv_nsec)
#define AS_TIMESPEC_TO_US(ts) ((ts).tv_sec*(as_ns_t)1e6 + (ts).tv_nsec/(as_ns_t)1e3)
#define AS_TIMESPEC_TO_MS(ts) ((ts).tv_sec*(as_ns_t)1e3 + (ts).tv_nsec/(as_ns_e)1e6)

/* types */
typedef uint64_t as_ns_t;
typedef uint64_t as_us_t;
typedef uint64_t as_ms_t;

/* error */
const char *
as_strerror (int code);

/* mutex */
AS_EXPORT int
as_mutex_init (as_mutex_t* mutex);
AS_EXPORT int
as_recursive_mutex_init (as_mutex_t* mutex);
AS_EXPORT void
as_mutex_destroy (as_mutex_t* mutex);
AS_EXPORT void
s_mutex_lock (as_mutex_t* mutex);
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
as_cond_timedwait (as_cond_t* cond, as_mutex_t* mutex, as_ms_t timeout);

/* barrier */
AS_EXPORT int
as_barrier_init (as_barrier_t* barrier, uint32_t count);
AS_EXPORT void
as_barrier_destroy (as_barrier_t* barrier);
AS_EXPORT void
as_barrier_wait (as_barrier_t* barrier);

/* semaphone */
AS_EXPORT int
as_sem_init (as_sem_t* sem);
AS_EXPORT int
as_sem_destroy (as_sem_t* sem);
AS_EXPORT void
as_sem_post (as_sem_t* sem);
AS_EXPORT void
as_sem_wait (as_sem_t* sem);
AS_EXPORT int
as_sem_timed_wait (as_sem_t* sem, as_ns_t timeout);

/* time */
AS_EXPORT as_ns_t
as_monotonic_time (int fast);
AS_EXPORT as_ns_t
as_system_time ();

#if defined(__cplusplus)
//extern }
#endif

#endif
