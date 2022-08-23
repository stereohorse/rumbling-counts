#include <stdio.h>

#include "test.h"

void test_start(const char* fn_name) {
	printf("%s...", fn_name);
}

int test_success() {
	printf("OK\n");
	return 0;
}

int test_fail() {
	printf("FAIL\n");
	return -1;
}
