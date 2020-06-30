#include "async.h"

#include <pthread.h>
#include <bits/local_lim.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int
as_mutex_init (as_mutex_t *mutex) {
  assert(mutex);
#if defined(NDEBUG) || !defined(PTHREAD_MUTEX_ERRORCHECK)
  return AS_ERRNO(pthread_mutex_init(mutex, NULL));
#else
  int err;
  pthread_mutexattr_t attr;

  if (pthread_mutexattr_init(&attr)
      || pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK))
    abort();

  err = pthread_mutex_init(mutex, &attr);

  if (pthread_mutexattr_destroy(&attr))
    abort();

  return AS_ERRNO(err);
#endif
}

int
as_recursive_mutex_init (as_mutex_t *mutex) {
  int err;
  pthread_mutexattr_t attr;

  if (pthread_mutexattr_init(&attr)
      || pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE))
    abort();

  err = pthread_mutex_init(mutex, &attr);

  if (pthread_mutexattr_destroy(&attr))
    abort();

  return AS_ERRNO(err);
}

void
as_mutex_destroy (as_mutex_t *mutex) {
  if (pthread_mutex_destroy(mutex))
    abort();
}

void
as_mutex_lock (as_mutex_t *mutex) {
  if (pthread_mutex_lock(mutex))
    abort();
}

void
as_mutex_unlock (as_mutex_t *mutex) {
  if (pthread_mutex_unlock(mutex))
    abort();
}

int
as_mutex_trylock (as_mutex_t *mutex) {
  int err;

  err = pthread_mutex_trylock(mutex);
  if (err) {
    if (EAGAIN == err || EBUSY == err)
      return AS_EBUSY;
    abort();
  }

  return AS_ESUCCESS;
}

/* rwlock */
int
as_rwlock_init (as_rwlock_t *rwlock) {
  return AS_ERRNO(pthread_rwlock_init(rwlock, NULL));
}

void
as_rwlock_destroy (as_rwlock_t *rwlock) {
  if (pthread_rwlock_destroy(rwlock))
    abort();
}

void
as_rwlock_rdlock (as_rwlock_t *rwlock) {
  if (pthread_rwlock_rdlock(rwlock))
    abort();
}

void
as_rwlock_rdunlock (as_rwlock_t *rwlock) {
  if (pthread_rwlock_unlock(rwlock))
    abort();
}

int
as_rwlock_rdtrylock (as_rwlock_t *rwlock) {
  int err;

  err = pthread_rwlock_tryrdlock(rwlock);
  if (err) {
    if (EAGAIN == err || EBUSY == err)
      return AS_EBUSY;
    abort();
  }
  return AS_ESUCCESS;
}

void
as_rwlock_wrlock (as_rwlock_t *rwlock) {
  if (pthread_rwlock_wrlock(rwlock))
    abort();
}

void
as_rwlock_wrunlock (as_rwlock_t *rwlock) {
  if (pthread_rwlock_unlock(rwlock))
    abort();
}

int
as_rwlock_wrtrylock (as_rwlock_t* rwlock) {
  int err;

  err = pthread_rwlock_trywrlock(rwlock);
  if (err) {
    if (EAGAIN == err || EBUSY == err)
      return AS_EBUSY;
    abort();
  }

  return AS_ESUCCESS;
}

int
as_cond_init (as_cond_t* cond) {
#if defined(AS_SYSTEM_DARWIN)
  return AS_ERRNO(pthread_cond_init(cond, NULL));
#else
  /* Using monotonic time */

  int err;
  pthread_condattr_t attr;

  if (pthread_condattr_init(&attr)
      || pthread_condattr_setclock(&attr, CLOCK_MONOTONIC))
    abort();

  err = pthread_cond_init(cond, &attr);

  if (pthread_condattr_destroy(&attr))
    abort();

  return AS_ERRNO(err);
#endif
}

void
as_cond_destroy (as_cond_t* cond) {
#if defined(AS_SYSTEM_DARWIN)
  /* It has been reported that destroying condition variables that have been
   * signalled but not waited on can sometimes result in application crashes.
   * See https://codereview.chromium.org/1323293005.
   */
  int err;
  pthread_mutex_t mutex;
  struct timespec ts;

  if (pthread_mutex_init(&mutex, NULL)
      || pthread_mutex_lock(&mutex))
    abort();

  ts.tv_sec = 0;
  ts.tv_nsec = 1;

  err = pthread_cond_timedwait_relative_np(cond, &mutex, &ts);
  if (err && ETIMEDOUT != err)
    abort();

  if (pthread_mutex_unlock(&mutex)
      || pthread_mutex_destroy(&mutex))
    abort();
#else
  if (pthread_cond_destroy(cond))
    abort();
#endif
}

void
as_cond_signal (as_cond_t* cond) {
  if (pthread_cond_signal(cond))
    abort();
}

void
as_cond_broadcast (as_cond_t* cond) {
  if (pthread_cond_broadcast(cond))
    abort();
}

void
as_cond_wait (as_cond_t* cond, as_mutex_t* mutex) {
  if (pthread_cond_wait(cond, mutex))
    abort();
}

int
as_cond_timedwait (as_cond_t* cond, as_mutex_t* mutex, as_ns_t timeout) {
  int err;
  struct timespec ts;

  timeout += as_monotonic_time(0);
  AS_NS_TO_TIMESPEC(ts, timeout);

#if defined(AS_SYSTEM_DARWIN)
  err = pthread_cond_timedwait_relative_np(cond, mutex, &ts);
#else
  err = pthread_cond_timedwait(cond, mutex, &ts);
  if (err && ETIMEDOUT != err)
    abort();
#endif

  return AS_ERRNO(err);
}

int
as_barrier_init (as_barrier_t* barrier, uint32_t count) {
  return AS_ERRNO(pthread_barrier_init(barrier, NULL, count));
}

void
as_barrier_destroy (as_barrier_t* barrier) {
  if (pthread_barrier_destroy(barrier))
    abort();
}

void
as_barrier_wait_and_destroy (as_barrier_t* barrier) {
  if (as_barrier_wait(barrier))
    as_barrier_destroy(barrier);
}

int
as_barrier_wait (as_barrier_t* barrier) {
  int err;

  err = pthread_barrier_wait(barrier);
  if (err && PTHREAD_BARRIER_SERIAL_THREAD != err)
    abort();

  return (err == PTHREAD_BARRIER_SERIAL_THREAD);
}

int
as_sem_init (as_sem_t* sem, unsigned int value) {
  return sem_init(sem, 0, value) ? AS_ERRNO(errno) : 0;
}

void
as_sem_destroy (as_sem_t* sem) {
  if (sem_destroy(sem))
    abort();
}

void
as_sem_post (as_sem_t* sem) {
  if (sem_post(sem))
    abort();
}

void
as_sem_wait (as_sem_t* sem) {
  int err;

  while ((err = sem_wait(sem)) < 0 && EINTR == errno)
    ;

  if (err < 0)
    abort();
}

int
as_sem_trywait (as_sem_t* sem) {
  int err;

  while ((err = sem_trywait(sem) < 0 && EINTR == errno))
    ;

  if (err < 0 && EAGAIN != errno)
    abort();

  return AS_ERRNO(errno);
}

int
as_thread_create (as_thread_t* t,
                  const as_thread_opts_t* opts,
                  as_thread_entry_cb entry,
                  void* args) {
  int err;
  pthread_attr_t attr;
  pthread_attr_t* attr_inited;
  size_t page_size;
  size_t stack_size;

  if (!entry)
    return AS_EINVAL;

  attr_inited = NULL;
  if (opts && opts->flags & AS_THREAD_FLAG_SET_STACK_SIZE) {
    page_size = getpagesize();
    stack_size = opts->stack_size;
    stack_size = (stack_size + page_size - 1) & ~(page_size - 1);
#if defined(PTHREAD_STACK_MIN)
    if (stack_size < PTHREAD_STACK_MIN)
      stack_size = PTHREAD_STACK_MIN;
#endif
    if (pthread_attr_init(&attr)
        || pthread_attr_setstacksize(&attr, stack_size))
      abort();
    attr_inited = &attr;
  }

  err = pthread_create(t, attr_inited, (void* (*)(void*))entry, args);

  if (attr_inited && pthread_attr_destroy(attr_inited))
    abort();

  return AS_ERRNO(err);
}

as_thread_t
as_thread_self (void) {
  return pthread_self();
}

as_tid_t
as_thread_tid (void) {
  return syscall(SYS_gettid);
}

int
as_thread_join (const as_thread_t* t) {
  return AS_ERRNO(pthread_join(*t, NULL));
}

int
as_thread_equal (const as_thread_t* t1, const as_thread_t* t2) {
  return pthread_equal(*t1, *t2);
}
