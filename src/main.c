#include <raylib.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600

int main(void)
{
	InitWindow(WIDTH, HEIGHT, "Analog Clock");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}