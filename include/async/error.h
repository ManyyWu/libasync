#ifndef ASYNC_ERROR_H
#define ASYNC_ERROR_H

#if defined(AS_SYSTEM_WIN32)
# include "async/win.h"
#else
# include "async/unix.h"
#endif

#include <errno.h>

#if EDOM > 0
# define AS_ERRNO(x)  (int)(-(x))
# define AS__ERRNO(x) (-(x))
#else
# define AS_ERRNO(x)  (int)(x)
# define AS__ERRNO(x) (x)
#endif

#define AS__ESUCCESS        (0)
#define AS__EUNKNOWN        (-4095)
#define AS__EOF             (-4094)

#define AS__EAI_ADDRFAMILY  (-3000)
#define AS__EAI_AGAIN       (-3001)
#define AS__EAI_BADFLAGS    (-3002)
#define AS__EAI_CANCELED    (-3003)
#define AS__EAI_FAIL        (-3004)
#define AS__EAI_FAMILY      (-3005)
#define AS__EAI_MEMORY      (-3006)
#define AS__EAI_NODATA      (-3007)
#define AS__EAI_NONAME      (-3008)
#define AS__EAI_OVERFLOW    (-3009)
#define AS__EAI_SERVICE     (-3010)
#define AS__EAI_SOCKTYPE    (-3011)
#define AS__EAI_BADHINTS    (-3013)
#define AS__EAI_PROTOCOL    (-3014)

/* Only map to the system errno on non-Windows platforms. It's apparently
 * a fairly common practice for Windows programmers to redefine errno codes.
 */

#if defined(ECHARSET) && !defined(AS_SYSTEM_WIN32)
# define AS__ECHARSET AS__ERRNO(ECHARSET)
#else
# define AS__ECHARSET (-4093)
#endif

#if defined(E2BIG) && !defined(AS_SYSTEM_WIN32)
# define AS__E2BIG AS__ERRNO(E2BIG)
#else
# define AS__E2BIG (-4092)
#endif

#if defined(EACCES) && !defined(AS_SYSTEM_WIN32)
# define AS__EACCES AS__ERRNO(EACCES)
#else
# define AS__EACCES (-4091)
#endif

#if defined(EADDRINUSE) && !defined(AS_SYSTEM_WIN32)
# define AS__EADDRINUSE AS__ERRNO(EADDRINUSE)
#else
# define AS__EADDRINUSE (-4090)
#endif

#if defined(EADDRNOTAVAIL) && !defined(AS_SYSTEM_WIN32)
# define AS__EADDRNOTAVAIL AS__ERRNO(EADDRNOTAVAIL)
#else
# define AS__EADDRNOTAVAIL (-4089)
#endif

#if defined(EAFNOSUPPORT) && !defined(AS_SYSTEM_WIN32)
# define AS__EAFNOSUPPORT AS__ERRNO(EAFNOSUPPORT)
#else
# define AS__EAFNOSUPPORT (-4088)
#endif

#if defined(EAGAIN) && !defined(AS_SYSTEM_WIN32)
# define AS__EAGAIN AS__ERRNO(EAGAIN)
#else
# define AS__EAGAIN (-4087)
#endif

#if defined(EALREADY) && !defined(AS_SYSTEM_WIN32)
# define AS__EALREADY AS__ERRNO(EALREADY)
#else
# define AS__EALREADY (-4086)
#endif

#if defined(EBADF) && !defined(AS_SYSTEM_WIN32)
# define AS__EBADF AS__ERRNO(EBADF)
#else
# define AS__EBADF (-4085)
#endif

#if defined(EBUSY) && !defined(AS_SYSTEM_WIN32)
# define AS__EBUSY AS__ERRNO(EBUSY)
#else
# define AS__EBUSY (-4084)
#endif

#if defined(ECANCELED) && !defined(AS_SYSTEM_WIN32)
# define AS__ECANCELED AS__ERRNO(ECANCELED)
#else
# define AS__ECANCELED (-4083)
#endif

#if defined(ECONNABORTED) && !defined(AS_SYSTEM_WIN32)
# define AS__ECONNABORTED AS__ERRNO(ECONNABORTED)
#else
# define AS__ECONNABORTED (-4082)
#endif

#if defined(ECONNREFUSED) && !defined(AS_SYSTEM_WIN32)
# define AS__ECONNREFUSED AS__ERRNO(ECONNREFUSED)
#else
# define AS__ECONNREFUSED (-4081)
#endif

#if defined(ECONNRESET) && !defined(AS_SYSTEM_WIN32)
# define AS__ECONNRESET AS__ERRNO(ECONNRESET)
#else
# define AS__ECONNRESET (-4080)
#endif

#if defined(EDESTADDRREQ) && !defined(AS_SYSTEM_WIN32)
# define AS__EDESTADDRREQ AS__ERRNO(EDESTADDRREQ)
#else
# define AS__EDESTADDRREQ (-4079)
#endif

#if defined(EEXIST) && !defined(AS_SYSTEM_WIN32)
# define AS__EEXIST AS__ERRNO(EEXIST)
#else
# define AS__EEXIST (-4078)
#endif

#if defined(EFAULT) && !defined(AS_SYSTEM_WIN32)
# define AS__EFAULT AS__ERRNO(EFAULT)
#else
# define AS__EFAULT (-4077)
#endif

#if defined(EFBIG) && !defined(AS_SYSTEM_WIN32)
# define AS__EFBIG AS__ERRNO(EFBIG)
#else
# define AS__EFBIG (-4076)
#endif

#if defined(EHOSTUNREACH) && !defined(AS_SYSTEM_WIN32)
# define AS__EHOSTUNREACH AS__ERRNO(EHOSTUNREACH)
#else
# define AS__EHOSTUNREACH (-4075)
#endif

#if defined(EINTR) && !defined(AS_SYSTEM_WIN32)
# define AS__EINTR AS__ERRNO(EINTR)
#else
# define AS__EINTR (-4074)
#endif

#if defined(EINVAL) && !defined(AS_SYSTEM_WIN32)
# define AS__EINVAL AS__ERRNO(EINVAL)
#else
# define AS__EINVAL (-4073)
#endif

#if defined(EIO) && !defined(AS_SYSTEM_WIN32)
# define AS__EIO AS__ERRNO(EIO)
#else
# define AS__EIO (-4072)
#endif

#if defined(EISCONN) && !defined(AS_SYSTEM_WIN32)
# define AS__EISCONN AS__ERRNO(EISCONN)
#else
# define AS__EISCONN (-4071)
#endif

#if defined(EISDIR) && !defined(AS_SYSTEM_WIN32)
# define AS__EISDIR AS__ERRNO(EISDIR)
#else
# define AS__EISDIR (-4070)
#endif

#if defined(ELOOP) && !defined(AS_SYSTEM_WIN32)
# define AS__ELOOP AS__ERRNO(ELOOP)
#else
# define AS__ELOOP (-4069)
#endif

#if defined(EMFILE) && !defined(AS_SYSTEM_WIN32)
# define AS__EMFILE AS__ERRNO(EMFILE)
#else
# define AS__EMFILE (-4068)
#endif

#if defined(EMSGSIZE) && !defined(AS_SYSTEM_WIN32)
# define AS__EMSGSIZE AS__ERRNO(EMSGSIZE)
#else
# define AS__EMSGSIZE (-4067)
#endif

#if defined(ENAMETOOLONG) && !defined(AS_SYSTEM_WIN32)
# define AS__ENAMETOOLONG AS__ERRNO(ENAMETOOLONG)
#else
# define AS__ENAMETOOLONG (-4065)
#endif

#if defined(ENETDOWN) && !defined(AS_SYSTEM_WIN32)
# define AS__ENETDOWN AS__ERRNO(ENETDOWN)
#else
# define AS__ENETDOWN (-4064)
#endif

#if defined(ENETUNREACH) && !defined(AS_SYSTEM_WIN32)
# define AS__ENETUNREACH AS__ERRNO(ENETUNREACH)
#else
# define AS__ENETUNREACH (-4063)
#endif

#if defined(ENFILE) && !defined(AS_SYSTEM_WIN32)
# define AS__ENFILE AS__ERRNO(ENFILE)
#else
# define AS__ENFILE (-4062)
#endif

#if defined(ENOBUFS) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOBUFS AS__ERRNO(ENOBUFS)
#else
# define AS__ENOBUFS (-4061)
#endif

#if defined(ENODEV) && !defined(AS_SYSTEM_WIN32)
# define AS__ENODEV AS__ERRNO(ENODEV)
#else
# define AS__ENODEV (-4060)
#endif

#if defined(ENOENT) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOENT AS__ERRNO(ENOENT)
#else
# define AS__ENOENT (-4059)
#endif

#if defined(ENOMEM) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOMEM AS__ERRNO(ENOMEM)
#else
# define AS__ENOMEM (-4058)
#endif

#if defined(ENONET) && !defined(AS_SYSTEM_WIN32)
# define AS__ENONET AS__ERRNO(ENONET)
#else
# define AS__ENONET (-4057)
#endif

#if defined(ENOPROTOOPT) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOPROTOOPT AS__ERRNO(ENOPROTOOPT)
#else
# define AS__ENOPROTOOPT (-4056)
#endif

#if defined(ENOSPC) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOSPC AS__ERRNO(ENOSPC)
#else
# define AS__ENOSPC (-4055)
#endif

#if defined(ENOSYS) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOSYS AS__ERRNO(ENOSYS)
#else
# define AS__ENOSYS (-4054)
#endif

#if defined(ENOTCONN) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOTCONN AS__ERRNO(ENOTCONN)
#else
# define AS__ENOTCONN (-4053)
#endif

#if defined(ENOTDIR) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOTDIR AS__ERRNO(ENOTDIR)
#else
# define AS__ENOTDIR (-4052)
#endif

#if defined(ENOTEMPTY) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOTEMPTY AS__ERRNO(ENOTEMPTY)
#else
# define AS__ENOTEMPTY (-4051)
#endif

#if defined(ENOTSOCK) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOTSOCK AS__ERRNO(ENOTSOCK)
#else
# define AS__ENOTSOCK (-4050)
#endif

#if defined(ENOTSUP) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOTSUP AS__ERRNO(ENOTSUP)
#else
# define AS__ENOTSUP (-4049)
#endif

#if defined(EPERM) && !defined(AS_SYSTEM_WIN32)
# define AS__EPERM AS__ERRNO(EPERM)
#else
# define AS__EPERM (-4048)
#endif

#if defined(EPIPE) && !defined(AS_SYSTEM_WIN32)
# define AS__EPIPE AS__ERRNO(EPIPE)
#else
# define AS__EPIPE (-4047)
#endif

#if defined(EPROTO) && !defined(AS_SYSTEM_WIN32)
# define AS__EPROTO AS__ERRNO(EPROTO)
#else
# define AS__EPROTO AS__ERRNO(4046)
#endif

#if defined(EPROTONOSUPPORT) && !defined(AS_SYSTEM_WIN32)
# define AS__EPROTONOSUPPORT AS__ERRNO(EPROTONOSUPPORT)
#else
# define AS__EPROTONOSUPPORT (-4045)
#endif

#if defined(EPROTOTYPE) && !defined(AS_SYSTEM_WIN32)
# define AS__EPROTOTYPE AS__ERRNO(EPROTOTYPE)
#else
# define AS__EPROTOTYPE (-4044)
#endif

#if defined(ERANGE) && !defined(AS_SYSTEM_WIN32)
# define AS__ERANGE AS__ERRNO(ERANGE)
#else
# define AS__ERANGE (-4043)
#endif

#if defined(EROFS) && !defined(AS_SYSTEM_WIN32)
# define AS__EROFS AS__ERRNO(EROFS)
#else
# define AS__EROFS (-4042)
#endif

#if defined(ESHUTDOWN) && !defined(AS_SYSTEM_WIN32)
# define AS__ESHUTDOWN AS__ERRNO(ESHUTDOWN)
#else
# define AS__ESHUTDOWN (-4041)
#endif

#if defined(ESPIPE) && !defined(AS_SYSTEM_WIN32)
# define AS__ESPIPE AS__ERRNO(ESPIPE)
#else
# define AS__ESPIPE (-4040)
#endif

#if defined(ESRCH) && !defined(AS_SYSTEM_WIN32)
# define AS__ESRCH AS__ERRNO(ESRCH)
#else
# define AS__ESRCH (-4039)
#endif

#if defined(ETIMEDOUT) && !defined(AS_SYSTEM_WIN32)
# define AS__ETIMEDOUT AS__ERRNO(ETIMEDOUT)
#else
# define AS__ETIMEDOUT (-4038)
#endif

#if defined(ETXTBSY) && !defined(AS_SYSTEM_WIN32)
# define AS__ETXTBSY AS__ERRNO(ETXTBSY)
#else
# define AS__ETXTBSY (-4037)
#endif

#if defined(EXDEV) && !defined(AS_SYSTEM_WIN32)
# define AS__EXDEV AS__ERRNO(EXDEV)
#else
# define AS__EXDEV (-4036)
#endif

#if defined(ENXIO) && !defined(AS_SYSTEM_WIN32)
# define AS__ENXIO AS__ERRNO(ENXIO)
#else
# define AS__ENXIO (-4035)
#endif

#if defined(EMLINK) && !defined(AS_SYSTEM_WIN32)
# define AS__EMLINK AS__ERRNO(EMLINK)
#else
# define AS__EMLINK (-4034)
#endif

/* EHOSTDOWN is not visible on BSD-like systems when _POSIX_C_SOURCE is
 * defined. Fortunately, its value is always 64 so it's possible albeit
 * icky to hard-code it.
 */
#if defined(EHOSTDOWN) && !defined(AS_SYSTEM_WIN32)
# define AS__EHOSTDOWN AS__ERRNO(EHOSTDOWN)
#elif defined(__APPLE__) or \
      defined(__DragonFly__) or \
      defined(__FreeBSD__) or \
      defined(__FreeBSD_kernel__) or \
      defined(__NetBSD__) or \
      defined(__OpenBSD__)
# define AS__EHOSTDOWN (-64)
#else
# define AS__EHOSTDOWN (-4033)
#endif

#if defined(EREMOTEIO) && !defined(AS_SYSTEM_WIN32)
# define AS__EREMOTEIO AS__ERRNO(EREMOTEIO)
#else
# define AS__EREMOTEIO (-4032)
#endif

#if defined(ENOTTY) && !defined(AS_SYSTEM_WIN32)
# define AS__ENOTTY AS__ERRNO(ENOTTY)
#else
# define AS__ENOTTY (-4031)
#endif

#if defined(EILSEQ) && !defined(AS_SYSTEM_WIN32)
# define AS__EILSEQ AS__ERRNO(EILSEQ)
#else
# define AS__EILSEQ (-4030)
#endif

#define AS_ERRNO_MAP(XX)                                               \
  XX(ESUCCESS,        "success")                                       \
  XX(EUNKNOWN,        "unknown error")                                 \
  XX(EOF,             "end of file")                                   \
  XX(E2BIG,           "argument list too long")                        \
  XX(EACCES,          "permission denied")                             \
  XX(EADDRINUSE,      "address already in use")                        \
  XX(EADDRNOTAVAIL,   "address not available")                         \
  XX(EAFNOSUPPORT,    "address family not supported")                  \
  XX(EAGAIN,          "resource temporarily unavailable")              \
  XX(EALREADY,        "connection already in progress")                \
  XX(EBADF,           "bad file descriptor")                           \
  XX(EBUSY,           "resource busy or locked")                       \
  XX(ECANCELED,       "operation canceled")                            \
  XX(ECONNABORTED,    "software caused connection abort")              \
  XX(ECONNREFUSED,    "connection refused")                            \
  XX(ECONNRESET,      "connection reset by peer")                      \
  XX(EDESTADDRREQ,    "destination address required")                  \
  XX(EEXIST,          "file already exists")                           \
  XX(EFAULT,          "bad address in system call argument")           \
  XX(EFBIG,           "file too large")                                \
  XX(EHOSTUNREACH,    "host is unreachable")                           \
  XX(EINTR,           "interrupted system call")                       \
  XX(EINVAL,          "invalid argument")                              \
  XX(EIO,             "i/o error")                                     \
  XX(EISCONN,         "socket is already connected")                   \
  XX(EISDIR,          "illegal operation on a directory")              \
  XX(ELOOP,           "too many symbolic links encountered")           \
  XX(EMFILE,          "too many open files")                           \
  XX(EMSGSIZE,        "message too long")                              \
  XX(ENAMETOOLONG,    "name too long")                                 \
  XX(ENETDOWN,        "network is down")                               \
  XX(ENETUNREACH,     "network is unreachable")                        \
  XX(ENFILE,          "file table overflow")                           \
  XX(ENOBUFS,         "no buffer space available")                     \
  XX(ENODEV,          "no such device")                                \
  XX(ENOENT,          "no such file or directory")                     \
  XX(ENOMEM,          "not enough memory")                             \
  XX(ENONET,          "machine is not on the network")                 \
  XX(ENOPROTOOPT,     "protocol not available")                        \
  XX(ENOSPC,          "no space left on device")                       \
  XX(ENOSYS,          "function not implemented")                      \
  XX(ENOTCONN,        "socket is not connected")                       \
  XX(ENOTDIR,         "not a directory")                               \
  XX(ENOTEMPTY,       "directory not empty")                           \
  XX(ENOTSOCK,        "socket operation on non-socket")                \
  XX(ENOTSUP,         "operation not supported on socket")             \
  XX(EPERM,           "operation not permitted")                       \
  XX(EPIPE,           "broken pipe")                                   \
  XX(EPROTO,          "protocol error")                                \
  XX(EPROTONOSUPPORT, "protocol not supported")                        \
  XX(EPROTOTYPE,      "protocol wrong type for socket")                \
  XX(ERANGE,          "result too large")                              \
  XX(EROFS,           "read-only file system")                         \
  XX(ESHUTDOWN,       "cannot send after transport endpoint shutdown") \
  XX(ESPIPE,          "invalid seek")                                  \
  XX(ESRCH,           "no such process")                               \
  XX(ETIMEDOUT,       "connection timed out")                          \
  XX(ETXTBSY,         "text file is busy")                             \
  XX(EXDEV,           "cross-device link not permitted")               \
  XX(ENXIO,           "no such device or address")                     \
  XX(EMLINK,          "too many links")                                \
  XX(EHOSTDOWN,       "host is down")                                  \
  XX(EREMOTEIO,       "remote I/O error")                              \
  XX(ENOTTY,          "inappropriate ioctl for device")                \
  XX(EILSEQ,          "illegal byte sequence")                         \
  XX(EAI_ADDRFAMILY,  "address family not supported")                  \
  XX(EAI_AGAIN,       "temporary failure")                             \
  XX(EAI_BADFLAGS,    "bad ai_flags value")                            \
  XX(EAI_BADHINTS,    "invalid value for hints")                       \
  XX(EAI_CANCELED,    "request canceled")                              \
  XX(EAI_FAIL,        "permanent failure")                             \
  XX(EAI_FAMILY,      "ai_family not supported")                       \
  XX(EAI_MEMORY,      "out of memory")                                 \
  XX(EAI_NODATA,      "no address")                                    \
  XX(EAI_NONAME,      "unknown node or service")                       \
  XX(EAI_OVERFLOW,    "argument buffer overflow")                      \
  XX(EAI_PROTOCOL,    "resolved protocol is unknown")                  \
  XX(EAI_SERVICE,     "service not available for socket type")         \
  XX(EAI_SOCKTYPE,    "socket type not supported")                     \

enum {
#define AS_ERRNO_ENUM_GEN(code, _) AS_##code = AS__##code,
  AS_ERRNO_MAP(AS_ERRNO_ENUM_GEN)
#undef AS_ERRNO_ENUM_GEN
};

#endif