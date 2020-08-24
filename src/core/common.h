#ifndef ASYNC_CORE_COMMON_H
#define ASYNC_CORE_COMMON_H
/*
#define as__check_param(exp)                                  \
  do {                                                        \
    if (!(exp) ? assert((exp)), 1 : 0)                        \
      return AS_EINVAL;                                       \
  } while (0)
*/
#define as__handleq_add(loop, handle)                         \
  do {                                                        \
    (handle)->flags |= AS_HANDLE_FLAG_REF;                    \
    as__handleq_insert((loop), (handle));                     \
  } while (0)

#define as__handleq_del(loop, handle)                         \
  do {                                                        \
    (handle)->flags &= ~AS_HANDLE_FLAG_REF;                   \
    as__handleq_remove((loop), (handle));                     \
  } while (0)

#define as__handle_start(loop, handle)                        \
  do {                                                        \
    if (as__handle_has_active((handle)))                      \
      break;                                                  \
    (handle)->flags |= AS_HANDLE_FLAG_ACTIVED;                \
    (loop)->actived_handles++;                                \
  } while (0)

#define as__handle_stop(loop, handle)                         \
  do {                                                        \
    if (!as__handle_has_active((handle)))                     \
      break;                                                  \
    (handle)->flags &= ~AS_HANDLE_FLAG_ACTIVED;               \
    (loop)->actived_handles--;                                \
  } while (0)

#define as__handle_has_ref(handle)                            \
  ((handle)->flags & AS_HANDLE_FLAG_REF)

#define as__handle_has_active(handle)                         \
  ((handle)->flags & AS_HANDLE_FLAG_ACTIVED)

#define as__handle_closing(handle)                            \
  ((handle)->flags & AS_HANDLE_FLAG_CLOSING)

#define as__handle_has_close(handle)                          \
  ((handle)->flags & AS_HANDLE_FLAG_CLOSED)

#define as__handleq_insert(loop, handle)                      \
  do {                                                        \
    list_add_tail((struct list_head *)(handle)->handleq_node, \
                  (struct list_head *)(loop)->handleq);       \
  } while (0)

#define as__handleq_remove(loop, handle)                      \
  do {                                                        \
    list_del_init((struct list_head *)(handle)->handleq_node);\
  } while (0)

#define as__pending_io_add(loop, io)                          \
  do {                                                        \
    list_add_tail((struct list_head *)(io)->pending_ioq,      \
                  (struct list_head *)(loop)->pending_ioq);   \
  } while (0)

#define as__pending_io_del(loop, handle)                      \
  do {                                                        \
    list_del_init((struct list_head *)(handle)->pending_ioq,  \
                  (struct list_head *)(loop)->pending_ioq);   \
  } while (0)

#endif