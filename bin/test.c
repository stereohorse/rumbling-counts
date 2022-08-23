#include <allegro5/allegro5.h>
#include <stdio.h>

#include "test_files.h"

void must(int return_code, const char *description) {
  if (return_code) {
    fprintf(stderr, "Unable to init test for%s", description);
    exit(0);
  }
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);

  must(test_files_init(), "files.c");
  should_return_null_if_file_not_exists();
  should_return_single_char_file();

  return 0;
}
