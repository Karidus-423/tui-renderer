#pragma once
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Triangle {
  Vector3 a;
  Vector3 b;
  Vector3 c;
} Polygon;

typedef struct TUIModel {
  Polygon *faces;
} TUIModel;

typedef enum Import_File_Type {
  OBJ,
  USD,
} Import_File_Type;

char *ReadFile(const char *filename);
TUIModel ImportModel(char *filename);
