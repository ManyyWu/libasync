#ifndef ASYNC_CORE_H
#define ASYNC_CORE_H

#include "async.h"

#define as__check_param(exp)             \
    do {                                 \
      if (!(exp) ? assert((exp)), 1 : 0) \
        return AS_EINVAL;                \
    } while (0)

#define as__handle_init(loop, handle)    \
    do {                                 \
      /* as__platform_init */            \
    } while (0)

#define as__handle_closing(handle)       \
    ((handle)->flags & AS_HANDLE_CLOSING)

#define as_handle_closed(handle)         \
    ((handle)->flags & AS_HANDLE_CLOSED)

#endif