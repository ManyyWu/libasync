#include "async.h"
#include <stdio.h>
#include <unistd.h>

int
main (int argc, char **argv) {
  fprintf(stderr, "%s\n", AS_VERSION);
  fprintf(stderr, "%" PRIu64 "\n", as_monotonic_time(1));
  sleep(1);
  fprintf(stderr, "%" PRIu64 "\n", as_monotonic_time(1));

  return 0;
}