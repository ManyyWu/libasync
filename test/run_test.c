#include "run_test.h"
#include "unit_list.h"

int
main (int argc, char **argv) {
  return run_tests(unit_tests_entry);
}