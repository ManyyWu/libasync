#include "async.h"

#include <pthread.h>
#include <stdlib.h>

int
as_mutex_init (as_mutex_t* mutex) {
#if defined(NDEBUG) || !defined(PTHREAD_MUTEX_ERRORCHECK)
  return pthread_mutex_init(mutex, NULL);
#else
#endif
}

int
as_recursive_mutex_init (as_mutex_t* mutex) {

}

void
as_mutex_destroy (as_mutex_t* mutex) {

}

void
s_mutex_lock (as_mutex_t* mutex) {

}

void
as_mutex_unlock (as_mutex_t* mutex) {

}

int
as_mutex_trylock (as_mutex_t* mutex) {

}


