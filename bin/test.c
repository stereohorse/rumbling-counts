#include <stdio.h>
#include <allegro5/allegro5.h>

#include "test_files.h"

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);

    should_return_null_if_file_not_exists();
    should_return_single_char_file();

    return 0;
}
