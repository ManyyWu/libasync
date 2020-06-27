#include "run_test.h"

static as_barrier_t s_barrier;

static void
thread_proc (void* args) {
  assert_true(args);
  *(as_thread_t *)args = as_thread_self();
  as_barrier_wait_and_destroy(&s_barrier);
}

UNIT_TEST(thread) {
  as_thread_t t;
  as_thread_t t1;
  as_thread_opts_t opts;

  assert_int_equal(as_thread_create(&t, NULL, NULL, NULL), AS_EINVAL);
  assert_int_equal(as_thread_create(&t, NULL, NULL, &t1), AS_EINVAL);

  as_barrier_init(&s_barrier, 2);
  assert_int_equal(as_thread_create(&t, NULL, thread_proc, &t1), 0);
  as_barrier_wait_and_destroy(&s_barrier);
  assert_int_not_equal(as_thread_equal(&t, &t1), 0);
  assert_int_equal(as_thread_join(&t), 0);
  assert_int_equal(as_thread_join(&t), AS_ESRCH);

  opts.flags = AS_THREAD_FLAG_SET_STACK_SIZE;
  opts.stack_size = 409600;
  as_barrier_init(&s_barrier, 2);
  assert_int_equal(as_thread_create(&t, &opts, thread_proc, &t1), 0);
  as_barrier_wait_and_destroy(&s_barrier);
  assert_int_not_equal(as_thread_equal(&t, &t1), 0);
  assert_int_equal(as_thread_join(&t), 0);
  assert_int_equal(as_thread_join(&t), AS_ESRCH);
}

static void
trace_callback (char* frame) {
  assert_true(frame);
  print_message2(frame);
}

UNIT_TEST(stack_trace) {
  assert_true(as_stack_trace(trace_callback) > 0);
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