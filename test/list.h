#include "cmockery.h"

TEST_DECLARE(version)
TEST_DECLARE(get_time)
TEST_DECLARE(strerror)

#ifdef _WIN32
TEST_DECLARE(win_sys_error)
#endif

TEST_LIST_START(unit_tests_entry)
  TEST_ENTRY(version)
  TEST_ENTRY(get_time)
  TEST_ENTRY(strerror)

#ifdef _WIN32
  TEST_ENTRY(error)
#endif
TEST_LIST_END
