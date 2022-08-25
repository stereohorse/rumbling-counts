#include <allegro5/allegro5.h>
#include <stdio.h>
#include <string.h>

#include "files.h"

#include "test.h"
#include "test_files.h"

int test_files_init(void) { return files_init(); }

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
  if (result == NULL) {
    return test_fail_msg("file not found");
  }

  if (strcmp("f\n", result)) {
    al_free(result);
    return test_fail_msg("unexpected char");
  }

  return test_success();
}
