#include "run_test.h"

as_barrier_t g_barrier;

static void
thread_proc (void *args) {
  assert_true(args);
  *(as_thread_t *)args = as_thread_self();
  as_barrier_wait_and_destroy(&g_barrier);
}

UNIT_TEST(thread) {
  as_thread_t t;
  as_thread_t t1;

  assert_int_equal(as_thread_create(&t, NULL, NULL, NULL), AS_EINVAL);
  assert_int_equal(as_thread_create(&t, NULL, NULL, &t1), AS_EINVAL);

  as_barrier_init(&g_barrier, 2);

  assert_int_equal(as_thread_create(&t, NULL, thread_proc, &t1), 0);
  as_barrier_wait_and_destroy(&g_barrier);
  assert_int_not_equal(as_thread_equal(&t, &t1), 0);
  //assert_int_equal(as_thread_join(&t), 0);
}

UNIT_TEST(sleep) {
  as_ns_t begin;
  as_ms_t diff;
  int i;

  for (i = 0; i < 100; ++i) {
    begin = as_monotonic_time(0);
    as_sleep(1);
    diff = (as_monotonic_time(0) - begin) / AS_USEC;
    assert_true(diff >= 1);
  }
}