#include <math.h>
#include <raylib.h>
#include <stdlib.h>

typedef struct Triangle {
  Vector2 p1;
  Vector2 p2;
  Vector2 p3;
} Triangle;

void TUIDrawPoints(Triangle tri) {
  DrawCircle(tri.p1.x, tri.p1.y, 3.0f, YELLOW);
  DrawCircle(tri.p2.x, tri.p2.y, 3.0f, RED);
  DrawCircle(tri.p3.x, tri.p3.y, 3.0f, GREEN);
}

void TUIDrawLine(Vector2 a, Vector2 b, Color c) {
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
      DrawCircle(y, x, 3.0f, c);
    } else {
      DrawCircle(x, y, 3.0f, c);
    }

    ierr += 2 * fabsf(b.y - a.y);
    y += ((b.y > a.y ? 1 : -1) * (ierr > b.x - a.x));
    ierr -= 2 * (b.x - a.x) * (ierr > b.x - a.x);
  }
}

Vector2 TUIRotatePoints(Vector2 p, double theta) {
  Vector2 prime = p;
  prime.x = p.x * cos(theta) - p.y * sin(theta);
  prime.y = p.y * sin(theta) - p.y * cos(theta);
  return prime;
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60);

  Triangle tri = {
      .p1 = {.x = screenWidth * 0.5, .y = screenHeight * 0.5},
      .p2 = {.x = screenWidth * 0.69, .y = screenHeight * 0.7},
      .p3 = {.x = screenWidth * 0.7, .y = screenHeight * 0.2},
  };

  double theta = 0;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKBLUE);

    TUIDrawLine(tri.p1, tri.p2, PURPLE);
    TUIDrawLine(tri.p2, tri.p3, ORANGE);
    TUIDrawLine(tri.p3, tri.p1, LIME);

    TUIDrawPoints(tri);

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
