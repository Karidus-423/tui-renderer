#include "import.h"
#include <stdio.h>
#include <stdlib.h>

char *ReadFile(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("fopen");
  }
  fseek(f, 0, SEEK_END);
  long length = ftell(f);
  rewind(f);
  char *bfr = malloc(sizeof(char) * length);

  fread(bfr, sizeof(char), length, f);

  fclose(f);
  return bfr;
}

// Import 3D OBJ file model.
TUIModel ImportOBJModel(char *fb) {
  size_t f_size = strlen(fb);
  printf("%s", fb);

  TUIModel model;
  return model;
}

// Import 3D file model.
TUIModel ImportModel(char *filename) {
  Import_File_Type format;
  char *file_bfr = ReadFile(filename);

  char *ft;
  char *track = filename;
  while ((ft = strtok_r(track, ".", &track))) {
    if (strcmp("obj", ft) == 0) {
      format = OBJ;
    } else if (strcmp("usd", ft) == 0) {
      format = USD;
    };
  }

  // switch (format) {
  // case OBJ:
  //   return ImportOBJModel(file_bfr);
  // }

  return ImportOBJModel(file_bfr);
}
