#include <stdio.h>
#include <string.h>

#include "files.h"

#include "test.h"
#include "test_files.h"

int should_return_null_if_file_not_exists(void) {
  test_start(__func__);

  char *result = files_read_all("non-existing path");
  if (!result) {
    return test_success();
  }

  return test_fail();
}

int should_return_single_char_file(void) {
  test_start(__func__);

  char *result = files_read_all("tests/data/single-char.txt");
  if (result != NULL && !strcmp("f", result)) {
    return test_success();
  }

  return test_fail();
}
