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

UNIT_TEST(cond) {
  as_mutex_t mutex;
  as_cond_t cond;

}