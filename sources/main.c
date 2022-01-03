#include <string.h>
#include <raylib.h>

#include "Entity2D.h"
#include "Paddle.h"

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	initEntity2D();
	initPaddle();
	void * p = new(Entity2D, 1, 2);
	void * paddleLeft = new(Paddle, 10, 160, 20, 80);
	void * paddleRight = new(Paddle, 770, 160, 20, 80);
	puto(p, stdout);
	printf("The position of p is %d %d\n", get_x(p), get_y(p));
	move(p, 2, 3);
	printf("The position of p is %d %d\n", get_x(p), get_y(p));
	const int screenWidth = 800;
	const int screenHeight = 400;

	InitWindow(screenWidth, screenHeight, "Pong game with raylib and Object Oriented C");

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

		//DrawLine(400, 0, 400, 400, DARKGRAY);
		DrawText("PONG", 400 - (MeasureText("PONG", 20) / 2), 10, 20, LIGHTGRAY);
		move(p, 400 - get_x(p), 200 - get_y(p));
		DrawCircle(get_x(p), get_y(p), 10.0, DARKGREEN);
		draw(paddleLeft);
		draw(paddleRight);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	delete(p);
	delete(paddleLeft);
	delete(paddleRight);
	//--------------------------------------------------------------------------------------

	return 0;
}
