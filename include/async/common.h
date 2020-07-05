#ifndef ASYNC_COMMON_H
#define ASYNC_COMMON_H

#include <stddef.h>

/* offset */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#undef offsetof
#if defined(__compiler_offsetof)
# define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE, MEMBER)
#else
# define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#undef offset
#if defined(__GNUC__)
#define container_of(ptr, type, member) ({               \
  const typeof( ((type *)0)->member ) *__mptr = (ptr);   \
  (type *)( (char *)__mptr - offsetof(type, member) );})
#else
# define container_of(ptr, type, member)                 \
  ((type *) ((char *) (ptr) - offsetof(type, member)))
#endif

/* unique id */
#if defined(__GNUC__)
# define AS_UNIQUE_ID(name) \
    __libasync_internal_##name##__COUNTER__
#else
    __libasync_internal_##name
#endif

/* log */
#define as_log_fatal(format, ...)                                                    \
  as_log(AS_LOG_FATAL  , __FILE__, __FUNCTION__, __LINE__, (format), ##__VA_ARGS__);
#define as_log_error(format, ...)                                                    \
  as_log(AS_LOG_ERROR  , __FILE__, __FUNCTION__, __LINE__, (format), ##__VA_ARGS__);
#define as_log_warning(format, ...)                                                  \
  as_log(AS_LOG_WARNING, __FILE__, __FUNCTION__, __LINE__, (format), ##__VA_ARGS__);
#define as_log_info(format, ...)                                                     \
  as_log(AS_LOG_INFO   , __FILE__, __FUNCTION__, __LINE__, (format), ##__VA_ARGS__);
#define as_log_debug(format, ...)                                                    \
  as_log(AS_LOG_DEBUG  , __FILE__, __FUNCTION__, __LINE__, (format), ##__VA_ARGS__);
#define as_log_trace(format, ...)                                                    \
  as_log(AS_LOG_TRACE  , __FILE__, __FUNCTION__, __LINE__, (format), ##__VA_ARGS__);

/* time */
#define AS_NSEC (as_time_t)1e9
#define AS_USEC (as_time_t)1e6
#define AS_MSEC (as_time_t)1e3

#define AS_TIMESPEC_TO_NS(ts)                                                         \
  ((ts).tv_sec*AS_NSEC + (ts).tv_nsec)
#define AS_TIMESPEC_TO_US(ts)                                                         \
  ((ts).tv_sec*AS_USEC + (ts).tv_nsec/AS_MSEC)
#define AS_TIMESPEC_TO_MS(ts)                                                         \
  ((ts).tv_sec*AS_MSEC + (ts).tv_nsec/AS_USEC)
#define AS_NS_TO_TIMESPEC(ts, ns)                                                     \
  do { (ts).tv_sec = (ns)/AS_NSEC; (ts).tv_nsec = (ns)%AS_NSEC; } while (0)
#define AS_US_TO_TIMESPEC(ts, us)                                                     \
  do { (ts).tv_sec = (us)/AS_USEC; (ts).tv_nsec = ((us)%AS_USEC)*AS_MSEC; } while (0)
#define AS_MS_TO_TIMESPEC(ts, ms)                                                     \
  do { (ts).tv_sec = (ms)/AS_MSEC; (ts).tv_nsec = ((ms)%AS_MSEC)*AS_USEC; } while (0)
#define AS_TIMEVAL_TO_US(tv)                                                          \
  ((tv).tv_sec*AS_USEC + (tv).tv_usec)
#define AS_TIMEVAL_TO_MS(tv)                                                          \
  ((tv).tv_sec*AS_MSEC + (tv).tv_usec/AS_MSEC)
#define AS_US_TO_TIMEVAL(tv, us)                                                      \
  do { (tv).tv_sec = (us)/AS_USEC; (tv).tv_usec = (us)%AS_USEC; } while (0)
#define AS_MS_TO_TIMEVAL(tv, ms)                                                      \
  do { (tv).tv_sec = (ms)/AS_MSEC; (tv).tv_usec = ((ms)%AS_MSEC)*AS_MSEC; } while (0)

#endif