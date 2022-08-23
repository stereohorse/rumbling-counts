#include <stddef.h>

#include <allegro5/allegro5.h>

#include "files.h"

char *files_read_all(const char *path) {
  if (path == NULL) {
    return NULL;
  }

  al_set_standard_file_interface();

  ALLEGRO_FILE *fp = al_fopen(path, "r");
  if (fp == NULL) {
    return NULL;
  }

  al_fclose(fp);

  return NULL;
}
