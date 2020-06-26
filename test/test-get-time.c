#include "run_test.h"

UNIT_TEST(get_time) {
  print_message2("monotonic time: %" PRIu64 "ns", as_monotonic_time(0));
  print_message2("monotonic time: %" PRIu64 "ns", as_monotonic_time(1));
  print_message2("system    time: %" PRIu64 "us", as_system_time());
}
