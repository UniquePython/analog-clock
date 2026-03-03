#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

#define DEG(x) ((x) * DEG2RAD)

void DrawClockFace(Color, Color, int);

int main(void)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(WIDTH, HEIGHT, "Analog Clock");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	RenderTexture2D clockFace = LoadRenderTexture(WIDTH, HEIGHT);
	BeginTextureMode(clockFace);
	ClearBackground(BLACK);
	DrawClockFace(RAYWHITE, RED, 10);
	EndTextureMode();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextureRec(
			clockFace.texture,
			(Rectangle){0, 0, WIDTH, -HEIGHT}, // flip vertically
			(Vector2){0, 0},
			WHITE);
		EndDrawing();
	}

	UnloadRenderTexture(clockFace);
	CloseWindow();

	return EXIT_SUCCESS;
}

void DrawClockFace(Color face, Color display, int padding)
{
	int cx = WIDTH / 2;
	int cy = HEIGHT / 2;
	int length = (HEIGHT < WIDTH ? HEIGHT : WIDTH) / 2 - padding;

	DrawCircle(cx, cy, length, face);
	DrawCircle(cx, cy, 5, display);

	int outer = length;
	int inner = length - 20;

	for (int angle = 0; angle < 360; angle += 6)
	{
		double rad = DEG(angle - 90);

		if (angle % 30 == 0)
		{
			double x1 = cx + inner * cos(rad);
			double y1 = cy + inner * sin(rad);

			double x2 = cx + outer * cos(rad);
			double y2 = cy + outer * sin(rad);

			DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, 5.0f, display);
		}
		else
		{
			double x1 = cx + (inner + 10) * cos(rad);
			double y1 = cy + (inner + 10) * sin(rad);

			double x2 = cx + outer * cos(rad);
			double y2 = cy + outer * sin(rad);

			DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, 2.5f, display);
		}
	}
}