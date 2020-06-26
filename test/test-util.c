#include "run_test.h"

UNIT_TEST(version) {
  char buf[32];

  sprintf(buf, "%d.%d.%d", AS_VERSION_MAJOR, AS_VERSION_MINOR, AS_VERSION_PATCH);
  assert_int_equal(strcmp(buf, AS_VERSION), 0);

  print_message("# version %s\n", AS_VERSION);
}
