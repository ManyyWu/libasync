#include "run_test.h"

UNIT_TEST(mutex) {
  as_mutex_t mutex;

  assert_int_equal(as_mutex_init(&mutex), 0);
  as_mutex_lock(&mutex);
  assert_int_equal(as_mutex_trylock(&mutex), AS_EBUSY);
  as_mutex_unlock(&mutex);
  as_mutex_destroy(&mutex);
}

UNIT_TEST(recursive_mutex) {
  as_mutex_t mutex;

  assert_int_equal(as_recursive_mutex_init(&mutex), 0);
  as_mutex_lock(&mutex);
  as_mutex_lock(&mutex);
  assert_int_equal(as_mutex_trylock(&mutex), 0);
  as_mutex_unlock(&mutex);
  as_mutex_unlock(&mutex);
  as_mutex_unlock(&mutex);
  as_mutex_destroy(&mutex);
}

UNIT_TEST(rwlock) {
  as_rwlock_t rwlock;

  as_rwlock_init(&rwlock);
  as_rwlock_wrlock(&rwlock);
  assert_int_equal(as_rwlock_wrtrylock(&rwlock), AS_EBUSY);
  assert_int_equal(as_rwlock_rdtrylock(&rwlock), AS_EBUSY);
  as_rwlock_wrunlock(&rwlock);
  as_rwlock_rdlock(&rwlock);
  assert_int_equal(as_rwlock_wrtrylock(&rwlock), AS_EBUSY);
  assert_int_equal(as_rwlock_rdtrylock(&rwlock), 0);
  as_rwlock_rdunlock(&rwlock);
  as_rwlock_rdunlock(&rwlock);
  as_rwlock_destroy(&rwlock);
}

static as_barrier_t s_barrier;
static as_mutex_t s_mutex;
static as_cond_t s_cond;
static int s_n;

static void
cond_test_thread_proc (void *args) {
  as_mutex_lock(&s_mutex);
  s_n++;
  as_cond_signal(&s_cond);
  as_mutex_unlock(&s_mutex);
}

static void
cond_test_thread_proc1 (void *args) {
  as_mutex_lock(&s_mutex);
  s_n++;
  as_cond_wait(&s_cond, &s_mutex);
  as_mutex_unlock(&s_mutex);
  as_cond_signal(&s_cond);
}

static void
cond_test_thread_proc2 (void *args) {
  as_mutex_lock(&s_mutex);
  s_n++;
  as_cond_wait(&s_cond, &s_mutex);
  as_mutex_unlock(&s_mutex);
  as_barrier_wait_and_destroy(&s_barrier);
}

UNIT_TEST(cond) {
#define THR_NUM 10
  int i;
  as_thread_t t[THR_NUM];

  assert_int_equal(as_mutex_init(&s_mutex), 0);
  assert_int_equal(as_cond_init(&s_cond), 0);

  // test 0
  s_n = 0;
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_create(&t[i], NULL, cond_test_thread_proc, NULL), 0);

  as_mutex_lock(&s_mutex);
  while (THR_NUM != s_n)
    as_cond_timedwait(&s_cond, &s_mutex, 1e6);
  as_mutex_unlock(&s_mutex);
  assert_int_equal(s_n, THR_NUM);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_join(&t[i]), 0);

  // test 1
  s_n = 0;
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_create(&t[i], NULL, cond_test_thread_proc1, NULL), 0);

  as_mutex_lock(&s_mutex);
  while (THR_NUM != s_n)
    as_cond_timedwait(&s_cond, &s_mutex, 1e6);
  as_mutex_unlock(&s_mutex);
  as_cond_signal(&s_cond);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_join(&t[i]), 0);

  // test 2
  s_n = 0;
  as_barrier_init(&s_barrier, THR_NUM + 1);
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_create(&t[i], NULL, cond_test_thread_proc2, NULL), 0);

  as_mutex_lock(&s_mutex);
  while (THR_NUM != s_n)
    as_cond_timedwait(&s_cond, &s_mutex, 1e6);
  as_mutex_unlock(&s_mutex);
  as_cond_broadcast(&s_cond);
  as_barrier_wait_and_destroy(&s_barrier);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_join(&t[i]), 0);

  as_mutex_destroy(&s_mutex);
  as_cond_destroy(&s_cond);
}

static void
barrier_test_thread_proc (void *args) {
  as_barrier_wait_and_destroy(&s_barrier);
}

UNIT_TEST(barrier) {
#undef THR_NUM
#define THR_NUM 10
  int i;
  as_thread_t t[THR_NUM];

  as_barrier_init(&s_barrier, THR_NUM + 1);
  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_create(&t[i], NULL, barrier_test_thread_proc, NULL), 0);

  as_barrier_wait_and_destroy(&s_barrier);

  for (i = 0; i < THR_NUM; ++i)
    assert_int_equal(as_thread_join(&t[i]), 0);
}

as_sem_t s_sem;

static void
sem_test_thread_proc (void *args) {
  as_sem_post(&s_sem);
  as_sem_post(&s_sem);
  as_sem_post(&s_sem);
}

UNIT_TEST(sem) {
  as_thread_t t;

  as_sem_init(&s_sem, 0);

  assert_int_equal(as_thread_create(&t, NULL, sem_test_thread_proc, NULL), 0);

  as_sem_wait(&s_sem);
  as_sem_wait(&s_sem);
  as_sem_wait(&s_sem);
  assert_int_equal(as_sem_trywait(&s_sem), AS_EAGAIN);

  assert_int_equal(as_thread_join(&t), 0);

  as_sem_destroy(&s_sem);
}