#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
		DrawClockHands(WIDTH / 2, HEIGHT / 2, (HEIGHT < WIDTH ? HEIGHT : WIDTH) / 2 - 10);
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

void DrawClockHands(int cx, int cy, int length)
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);

	float hourAngle = ((t->tm_hour % 12) + t->tm_min / 60.0f) * 30.0f;
	float minuteAngle = (t->tm_min + t->tm_sec / 60.0f) * 6.0f;
	float secondAngle = t->tm_sec * 6.0f;

	float hourLength = length * 0.5f;
	float minuteLength = length * 0.75f;
	float secondLength = length * 0.9f;

	Vector2 center = {cx, cy};

	Vector2 hourEnd = {cx + hourLength * cos(DEG(hourAngle - 90)),
					   cy + hourLength * sin(DEG(hourAngle - 90))};

	Vector2 minuteEnd = {cx + minuteLength * cos(DEG(minuteAngle - 90)),
						 cy + minuteLength * sin(DEG(minuteAngle - 90))};

	Vector2 secondEnd = {cx + secondLength * cos(DEG(secondAngle - 90)),
						 cy + secondLength * sin(DEG(secondAngle - 90))};

	DrawLineEx(center, hourEnd, 8.0f, RED);
	DrawLineEx(center, minuteEnd, 5.0f, PURPLE);
	DrawLineEx(center, secondEnd, 2.0f, GREEN);
}