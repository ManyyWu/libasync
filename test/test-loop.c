#include "run_test.h"

UNIT_TEST(loop) {
  as_loop_t *loop;

  loop = as_default_loop();
  assert_true(loop);
  assert_int_equal(as_run(loop), 0);
  assert_int_equal(as_loop_close(loop), 0);
}
