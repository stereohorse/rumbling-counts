#ifndef TEST_H
#define TEST_H

void test_start(const char *fn_name);
int test_success(void);
int test_fail(void);
int test_fail_msg(const char *msg);

#endif
