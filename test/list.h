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
TEST_DECLARE(barrier)
TEST_DECLARE(sem)
TEST_DECLARE(thread)
TEST_DECLARE(stack_trace)
TEST_DECLARE(sleep)
TEST_DECLARE(doubly_list)
TEST_DECLARE(heap)

#ifdef _WIN32
TEST_DECLARE(win_sys_error)
#endif

#if 0
TEST_LIST_START(unit_tests_entry)
  TEST_ENTRY(version)
  TEST_ENTRY(macros)
  TEST_ENTRY(once)
  TEST_ENTRY(get_time)
  TEST_ENTRY(strerror)
  TEST_ENTRY(mutex)
  TEST_ENTRY(recursive_mutex)
  TEST_ENTRY(cond)
  TEST_ENTRY(barrier)
  TEST_ENTRY(sem)
  TEST_ENTRY(thread)
  TEST_ENTRY(stack_trace)
  TEST_ENTRY(sleep)
  TEST_ENTRY(doubly_list)
  TEST_ENTRY(heap)

#ifdef _WIN32
  TEST_ENTRY(error)
#endif
TEST_LIST_END
#else
TEST_LIST_START(unit_tests_entry)
  TEST_ENTRY(heap)
TEST_LIST_END
#endif
