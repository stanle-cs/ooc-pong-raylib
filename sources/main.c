#include <raylib.h>

#include "Entity2D.h"

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	initEntity2D();
	void * p = new(Entity2D, 1, 2);
	puto(p, stdout);
	printf("The position of p is %d %d\n", get_x(p), get_y(p));
	move(p, 2, 3);
	printf("The position of p is %d %d\n", get_x(p), get_y(p));
	delete(p);
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
