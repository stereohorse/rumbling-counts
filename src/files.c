#include <stddef.h>

#include <allegro5/allegro5.h>

#include "files.h"

int files_init(void) {
  al_set_standard_file_interface();
  return 0;
}

/**
 * Function: files_read_all
 * ------------------------
 * reads entire file content into memory
 *
 *  path: path to file to read
 *
 *  returns: pointer to bytes read; caller must free the memory after usage
 */
char *files_read_all(const char *path) {
  if (path == NULL) {
    return NULL;
  }

  ALLEGRO_FILE *fp = al_fopen(path, "r");
  if (fp == NULL) {
    return NULL;
  }

  size_t buf_size = 4096;
  char buf[buf_size];

  size_t result_size = buf_size;
  size_t remaining_result_size = buf_size;
  char *result = al_malloc(result_size);

  size_t bytes_read;
  do {
    bytes_read = al_fread(fp, buf, buf_size);
    if (al_ferror(fp)) {
      al_free(result);
      return NULL;
    }

    if (bytes_read > remaining_result_size) {
      char *new_result = al_malloc(result_size + buf_size);
      memcpy(new_result, result, result_size);
      al_free(result);

      result = new_result;
      result_size += buf_size;
      remaining_result_size += buf_size;
    }

    memcpy(result + (result_size - remaining_result_size), buf, bytes_read);
    remaining_result_size -= bytes_read;
  } while (!al_feof(fp));

  al_fclose(fp);

  return result;
}
