#include "run_test.h"

void
timer_once (as_timer_t *handle) {
  assert_int_equal(as_timer_stop(handle), 0);

  print_message2("timer_once");
}

void
timer_persist (as_timer_t *handle) {
  static int times = 0;

  if (++times > 3) {
    assert_int_equal(as_timer_stop(handle), 0);
    return;
  }

  print_message2("timer_persist");
}

UNIT_TEST(timer) {
  as_loop_t loop;
  as_timer_t timer;
  as_timer_t timer1;

  assert_int_equal(as_loop_init(&loop), 0);

  assert_int_equal(as_timer_init(&loop, &timer), 0);
  assert_int_equal(as_timer_init(&loop, &timer1), 0);

  assert_int_equal(as_timer_start(&timer, 1000, 0, timer_once), 0);
  assert_int_equal(as_timer_start(&timer1, 1000, 1000, timer_persist), 0);

  assert_int_equal(as_timer_expired(&timer), 0);
  assert_int_equal(as_timer_expired(&timer1), 0);

  assert_int_equal(as_run(&loop), 0);

  assert_int_equal(as_timer_expired(&timer), 1);
  assert_int_equal(as_timer_expired(&timer1), 1);

  assert_int_equal(as_loop_close(&loop), 0);

  assert_int_equal(as_timer_stop(&timer), AS_EINVAL);
  assert_int_equal(as_timer_stop(&timer1), AS_EINVAL);
}
