#include "run_test.h"

UNIT_TEST(get_time) {
  assert_in_range(as_monotonic_time(1), 0, UINT64_MAX);
  assert_in_range(as_monotonic_time(-1), 0, UINT64_MAX);
  assert_in_range(as_monotonic_time(0), 0, UINT64_MAX);
}
