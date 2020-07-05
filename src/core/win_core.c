#include "core/win_core.h"

int
as__loop_init_platform (as_loop_t *loop) {

}

void
as__loop_close_platform (as_loop_t *loop) {

}

int
as__io_poll_platform (as_loop_t *loop, as_ms_t timeout) {

}

int
as_translate_sys_error (DWORD code) {
  if (code <= 0)
    return code; // already a libasync error code

  switch (code) {
    case ERROR_NOACCESS:                   return AS_EACCES;
    case WSAEACCES:                        return AS_EACCES;
    case ERROR_ELEVATION_REQUIRED:         return AS_EACCES;
    case ERROR_ADDRESS_ALREADY_ASSOCIATED: return AS_EADDRINUSE;
    case WSAEADDRINUSE:                    return AS_EADDRINUSE;
    case WSAEADDRNOTAVAIL:                 return AS_EADDRNOTAVAIL;
    case WSAEAFNOSUPPORT:                  return AS_EAFNOSUPPORT;
    case WSAEWOULDBLOCK:                   return AS_EAGAIN;
    case WSAEALREADY:                      return AS_EALREADY;
    case ERROR_INVALID_FLAGS:              return AS_EBADF;
    case ERROR_INVALID_HANDLE:             return AS_EBADF;
    case ERROR_LOCK_VIOLATION:             return AS_EBUSY;
    case ERROR_PIPE_BUSY:                  return AS_EBUSY;
    case ERROR_SHARING_VIOLATION:          return AS_EBUSY;
    case WAIT_TIMEOUT:                     return AS_EBUSY;
    case ERROR_OPERATION_ABORTED:          return AS_ECANCELED;
    case WSAEINTR:                         return AS_ECANCELED;
    case ERROR_NO_UNICODE_TRANSLATION:     return AS_ECHARSET;
    case ERROR_CONNECTION_ABORTED:         return AS_ECONNABORTED;
    case WSAECONNABORTED:                  return AS_ECONNABORTED;
    case ERROR_CONNECTION_REFUSED:         return AS_ECONNREFUSED;
    case WSAECONNREFUSED:                  return AS_ECONNREFUSED;
    case ERROR_NETNAME_DELETED:            return AS_ECONNRESET;
    case WSAECONNRESET:                    return AS_ECONNRESET;
    case ERROR_ALREADY_EXISTS:             return AS_EEXIST;
    case ERROR_FILE_EXISTS:                return AS_EEXIST;
    case ERROR_BUFFER_OVERFLOW:            return AS_EFAULT;
    case WSAEFAULT:                        return AS_EFAULT;
    case ERROR_HOST_UNREACHABLE:           return AS_EHOSTUNREACH;
    case WSAEHOSTUNREACH:                  return AS_EHOSTUNREACH;
    case ERROR_INSUFFICIENT_BUFFER:        return AS_EINVAL;
    case ERROR_INVALID_DATA:               return AS_EINVAL;
    case ERROR_INVALID_PARAMETER:          return AS_EINVAL;
    case ERROR_SYMLINK_NOT_SUPPORTED:      return AS_EINVAL;
    case WSAEINVAL:                        return AS_EINVAL;
    case WSAEPFNOSUPPORT:                  return AS_EINVAL;
    case WSAESOCKTNOSUPPORT:               return AS_EINVAL;
    case ERROR_BEGINNING_OF_MEDIA:         return AS_EIO;
    case ERROR_BUS_RESET:                  return AS_EIO;
    case ERROR_CRC:                        return AS_EIO;
    case ERROR_DEVICE_DOOR_OPEN:           return AS_EIO;
    case ERROR_DEVICE_REQUIRES_CLEANING:   return AS_EIO;
    case ERROR_DISK_CORRUPT:               return AS_EIO;
    case ERROR_EOM_OVERFLOW:               return AS_EIO;
    case ERROR_FILEMARK_DETECTED:          return AS_EIO;
    case ERROR_GEN_FAILURE:                return AS_EIO;
    case ERROR_INVALID_BLOCK_LENGTH:       return AS_EIO;
    case ERROR_IO_DEVICE:                  return AS_EIO;
    case ERROR_NO_DATA_DETECTED:           return AS_EIO;
    case ERROR_NO_SIGNAL_SENT:             return AS_EIO;
    case ERROR_OPEN_FAILED:                return AS_EIO;
    case ERROR_SETMARK_DETECTED:           return AS_EIO;
    case ERROR_SIGNAL_REFUSED:             return AS_EIO;
    case WSAEISCONN:                       return AS_EISCONN;
    case ERROR_CANT_RESOLVE_FILENAME:      return AS_ELOOP;
    case ERROR_TOO_MANY_OPEN_FILES:        return AS_EMFILE;
    case WSAEMFILE:                        return AS_EMFILE;
    case WSAEMSGSIZE:                      return AS_EMSGSIZE;
    case ERROR_FILENAME_EXCED_RANGE:       return AS_ENAMETOOLONG;
    case ERROR_NETWORK_UNREACHABLE:        return AS_ENETUNREACH;
    case WSAENETUNREACH:                   return AS_ENETUNREACH;
    case WSAENOBUFS:                       return AS_ENOBUFS;
    case ERROR_BAD_PATHNAME:               return AS_ENOENT;
    case ERROR_DIRECTORY:                  return AS_ENOENT;
    case ERROR_ENVVAR_NOT_FOUND:           return AS_ENOENT;
    case ERROR_FILE_NOT_FOUND:             return AS_ENOENT;
    case ERROR_INVALID_NAME:               return AS_ENOENT;
    case ERROR_INVALID_DRIVE:              return AS_ENOENT;
    case ERROR_INVALID_REPARSE_DATA:       return AS_ENOENT;
    case ERROR_MOD_NOT_FOUND:              return AS_ENOENT;
    case ERROR_PATH_NOT_FOUND:             return AS_ENOENT;
    case WSAHOST_NOT_FOUND:                return AS_ENOENT;
    case WSANO_DATA:                       return AS_ENOENT;
    case ERROR_NOT_ENOUGH_MEMORY:          return AS_ENOMEM;
    case ERROR_OUTOFMEMORY:                return AS_ENOMEM;
    case ERROR_CANNOT_MAKE:                return AS_ENOSPC;
    case ERROR_DISK_FULL:                  return AS_ENOSPC;
    case ERROR_EA_TABLE_FULL:              return AS_ENOSPC;
    case ERROR_END_OF_MEDIA:               return AS_ENOSPC;
    case ERROR_HANDLE_DISK_FULL:           return AS_ENOSPC;
    case ERROR_NOT_CONNECTED:              return AS_ENOTCONN;
    case WSAENOTCONN:                      return AS_ENOTCONN;
    case ERROR_DIR_NOT_EMPTY:              return AS_ENOTEMPTY;
    case WSAENOTSOCK:                      return AS_ENOTSOCK;
    case ERROR_NOT_SUPPORTED:              return AS_ENOTSUP;
    case ERROR_BROKEN_PIPE:                return AS_EOF;
    case ERROR_ACCESS_DENIED:              return AS_EPERM;
    case ERROR_PRIVILEGE_NOT_HELD:         return AS_EPERM;
    case ERROR_BAD_PIPE:                   return AS_EPIPE;
    case ERROR_NO_DATA:                    return AS_EPIPE;
    case ERROR_PIPE_NOT_CONNECTED:         return AS_EPIPE;
    case WSAESHUTDOWN:                     return AS_EPIPE;
    case WSAEPROTONOSUPPORT:               return AS_EPROTONOSUPPORT;
    case ERROR_WRITE_PROTECT:              return AS_EROFS;
    case ERROR_SEM_TIMEOUT:                return AS_ETIMEDOUT;
    case WSAETIMEDOUT:                     return AS_ETIMEDOUT;
    case ERROR_NOT_SAME_DEVICE:            return AS_EXDEV;
    case ERROR_INVALID_FUNCTION:           return AS_EISDIR;
    case ERROR_META_EXPANSION_TOO_LONG:    return AS_E2BIG;
    default:                               break;
  }
  return AS_EUNKNOWN;
}
