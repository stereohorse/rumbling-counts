#include <stdio.h>

#include "test.h"

void test_start(const char *fn_name) { printf("%s...", fn_name); }

int test_success(void) {
  printf("OK\n");
  return 0;
}

int test_fail(void) {
  printf("FAIL\n");
  return -1;
}

int test_fail_msg(const char *msg) {
  printf("FAIL: %s\n", msg);
  return -1;
}
