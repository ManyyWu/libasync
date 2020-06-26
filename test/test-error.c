#include "run_test.h"
#ifdef _WIN32
#include "core/win_core.h"
#endif

UNIT_TEST(strerror) {
  assert_int_equal(AS_ESUCCESS, 0);
  assert_int_equal(AS_EUNKNOWN, -4095);
  assert_int_equal(AS_EOF, -4094);

  assert_int_equal(strcmp(as_strerror(AS_ESUCCESS), "success"), 0);
  assert_int_equal(strcmp(as_strerror(AS_EUNKNOWN), "unknown error"), 0);
  assert_int_equal(strcmp(as_strerror(-4096), "unknown error"), 0);
}

#ifdef _WIN32
NIT_TEST(win_sys_error) {
  assert_int_equal(as_translate_sys_error(EINVAL), -EINVAL);
  assert_int_equal(as_translate_sys_error(AS_ESUCCESS), AS_ESUCCESS);
  assert_int_equal(as_translate_sys_error(AS_EINVAL), AS_EINVAL);
}
#endif
