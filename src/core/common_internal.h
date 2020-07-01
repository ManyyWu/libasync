#ifndef ASYNC_COMMON_INTERNAL_H
#define ASYNC_COMMON_INTERNAL_H

#define as__check_param(exp)                                \
  do {                                                      \
    if (!(exp) ? assert((exp)), 1 : 0)                      \
      return AS_EINVAL;                                     \
  } while (0)

#define as__handle_init(loop, handle)                       \
  do {                                                      \
    if (as__handle_has_ref(handle))                         \
      break;                                                \
    handle->flags |= AS_HANDLE_FLAG_REF;                    \
    as__handleq_insert(handle);                             \
    /* as__platform_init */                                 \
  } while (0)

#define as__handle_deinit(loop, handle)                     \
  do {                                                      \
    if (!as__handle_has_ref(handle))                        \
      break;                                                \
    handle->flags &= ~AS_HANDLE_FLAG_REF;                   \
    as__handleq_remove(handle);                             \
    /* as__platform_deinit */                               \
  } while (0)

#define as__handle_start(loop, handle)                      \
  do {                                                      \
    if (as__handle_has_active(handle))                      \
      break;                                                \
    handle->flags |= AS_HANDLE_FLAG_ACTIVED;                \
    loop->actived_handles++;                                \
  } while (0)

#define as__handle_stop(loop, handle)                       \
  do {                                                      \
    if (!as__handle_has_active(handle))                     \
      break;                                                \
    handle->flags &= ~AS_HANDLE_FLAG_ACTIVED;               \
    loop->actived_handles--;                                \
  } while (0)

#define as__handle_has_ref(handle)                          \
  ((handle)->flags & AS_HANDLE_FLAG_REF)

#define as__handle_has_active(handle)                       \
  ((handle)->flags & AS_HANDLE_FLAG_ACTIVED)

#define as__handle_closing(handle)                          \
  ((handle)->flags & AS_HANDLE_FLAG_CLOSING)

#define as__handle_has_close(handle)                        \
  ((handle)->flags & AS_HANDLE_FLAG_CLOSED)

#define as__handleq_insert(handle)                          \
  do {                                                      \
    list_add_tail((struct list_head *)handle->handleq_node, \
                  (struct list_head *)loop->handleq);       \
  } while (0)

#define as__handleq_remove(handle)                          \
  do {                                                      \
    list_del_init((struct list_head *)handle->handleq_node, \
                  (struct list_head *)loop->handleq);       \
  } while (0)


#endif