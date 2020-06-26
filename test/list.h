#include "cmockery.h"

TEST_DECLARE(version)
TEST_DECLARE(macros)
TEST_DECLARE(once)
TEST_DECLARE(get_time)
TEST_DECLARE(strerror)
TEST_DECLARE(mutex)
TEST_DECLARE(recursive_mutex)
TEST_DECLARE(rwlock)
TEST_DECLARE(cond)
TEST_DECLARE(thread)
TEST_DECLARE(sleep)

#ifdef _WIN32
TEST_DECLARE(win_sys_error)
#endif

TEST_LIST_START(unit_tests_entry)
  TEST_ENTRY(version)
  TEST_ENTRY(macros)
  TEST_ENTRY(once)
  TEST_ENTRY(get_time)
  TEST_ENTRY(strerror)
  TEST_ENTRY(mutex)
  TEST_ENTRY(recursive_mutex)
  TEST_ENTRY(cond)
  TEST_ENTRY(thread)
  TEST_ENTRY(sleep)

#ifdef _WIN32
  TEST_ENTRY(error)
#endif
TEST_LIST_END
