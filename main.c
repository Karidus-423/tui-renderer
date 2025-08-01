#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Triangle {
  Vector2 a;
  Vector2 b;
  Vector2 c;
} Polygon;

typedef struct TUIModel {
  Polygon *faces;
} TUIModel;

void TUIDrawLine(Vector2 a, Vector2 b, Color color) {
  // Swap directions to always be left to right.
  bool steep = fabsf(a.y - b.y) > fabsf(a.x - b.x);
  if (steep) {
    Vector2 tmp_a = a;
    Vector2 tmp_b = b;

    a.x = tmp_a.y;
    a.y = tmp_a.x;
    b.x = tmp_b.y;
    b.y = tmp_b.x;
  }

  if (a.x > b.x) {
    float tmp_x = a.x;
    float tmp_y = a.y;
    a.x = b.x;
    a.y = b.y;
    b.x = tmp_x;
    b.y = tmp_y;
  }

  int y = a.y;
  int ierr = 0;
  for (int x = a.x; x <= b.x; ++x) {
    if (steep) {
      DrawCircle(y, x, 3.0f, color);
    } else {
      DrawCircle(x, y, 3.0f, color);
    }

    ierr += 2 * fabsf(b.y - a.y);
    y += ((b.y > a.y ? 1 : -1) * (ierr > b.x - a.x));
    ierr -= 2 * (b.x - a.x) * (ierr > b.x - a.x);
  }
}

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

  return bfr;
}

TUIModel ImportModel(const char *filename) {
  // Count Vertices and Faces in filename
  int verts, faces = 0;
  char *v;
  char *f;

  char *bfr = ReadFile(filename);

  printf("File: %s", bfr);

  TUIModel model[faces];

  return *model;
}

int main() {
  const int screenWidth = 850;
  const int screenHeight = 1200;
  InitWindow(screenWidth, screenHeight, "Future TUI Renderer");
  SetTargetFPS(60);

  TUIModel model = ImportModel("./spot/spot_triangulated.obj");

  double theta = 0;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKBLUE);

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
