#include <sys/types.h>

#include <semaphore.h>
#include <pthread.h>

#if defined(AS_SYSTEM_MACOSX)
# include "async/darwin.h"
#endif

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



