#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include <raylib.h>

#include "Entity2D.h"
#include "Paddle.h"

void generateRandom(int * x, int * y, int SPEED)
{
	float fX = 0.0;
	float fY = 0.0;
	do 
	{
		fX = ((double)rand() / (double)(RAND_MAX)) * 2.0 - 1.0;
		fY = ((double)rand() / (double)(RAND_MAX)) * 2.0 - 1.0;
	} while (fY == 0 || fX == 0 || fabs(fX - fY) >= 0.7);

	*x = (int) round(fX * SPEED);
	*y = (int) round(fY * SPEED);
}


int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	srand(time(NULL));
	initEntity2D();
	initPaddle();

	void *ball = new (Entity2D, 400, 200, RAYWHITE);
	void *paddleLeft = new (Paddle, 10, 160, RAYWHITE, 20, 80);
	void *paddleRight = new (Paddle, 770, 160, RAYWHITE, 20, 80);
	int ballX = 0;
	int ballY = 0;

	int leftScore = 0;
	int rightScore = 0;
	char leftText[10];
	char rightText[10];
	
	float lastUpdate = 0;
	float currentSpeed = 0;

	const int SPEED = 3;
	const int screenWidth = 800;
	const int screenHeight = 400;

	generateRandom(&ballX, &ballY, SPEED);

	currentSpeed = SPEED;

	InitWindow(screenWidth, screenHeight, "Pong game with raylib and Object Oriented C");
	lastUpdate = GetTime();

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		Rectangle paddleLeftRect = (Rectangle){get_x(paddleLeft), get_y(paddleLeft), get_w(paddleLeft), get_h(paddleLeft)};
		Rectangle paddleRightRect = (Rectangle){get_x(paddleRight), get_y(paddleRight), get_w(paddleRight), get_h(paddleRight)};
		Vector2 ballCirc = (Vector2){get_x(ball), get_y(ball)};

		if (IsKeyDown(KEY_S))
		{
			if (paddleLeftRect.y < 400 - 80)
				move(paddleLeft, 0, 1);
		}
		if (IsKeyDown(KEY_W))
		{
			if (paddleLeftRect.y > 0)
				move(paddleLeft, 0, -1);
		}
		if (IsKeyDown(KEY_DOWN))
		{
			if (paddleRightRect.y < 400 - 80)
				move(paddleRight, 0, 1);
		}
		if (IsKeyDown(KEY_UP))
		{
			if (paddleRightRect.y > 0)
				move(paddleRight, 0, -1);
		}

		if (ballCirc.y <= 5 || ballCirc.y >= screenHeight - 5)
		{
			ballY = -ballY;
		}

		if (CheckCollisionCircleRec(ballCirc, 10.0, paddleLeftRect))
		{
			if (GetTime() - lastUpdate > 0.2)
				if (ballX < 0) ballX = -ballX;
			lastUpdate = GetTime();
		}

		if (CheckCollisionCircleRec(ballCirc, 10.0, paddleRightRect))
		{
			if (GetTime() - lastUpdate > 0.2)
				if (ballX > 0) ballX = -ballX;
			lastUpdate = GetTime();
		}

		if ((ballCirc.x >= 0 && ballCirc.x <= screenWidth))
		{
			move(ball, ballX, ballY);
		}
		else
		{
			if (ballCirc.x < 0) rightScore++;
			if (ballCirc.x > screenWidth) leftScore++;
			generateRandom(&ballX, &ballY, currentSpeed);
			set_position(ball, 400, 200);
			if (currentSpeed <= 15) currentSpeed *= 1.15;
		}

		sprintf(leftText, "%03d", leftScore);
		sprintf(rightText, "%03d", rightScore);

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		//DrawLine(400, 0, 400, 400, DARKGRAY);
		DrawFPS(1, 0);
		DrawText("PONG", 400 - (MeasureText("PONG", 20) / 2), 10, 20, RAYWHITE);
		DrawText(leftText, 10, 30, 30, RAYWHITE);
		DrawText(rightText, 790 - (MeasureText(rightText, 30)), 30, 30, RAYWHITE);

		DrawCircle(ballCirc.x, ballCirc.y, 10.0, get_color(ball));
		draw(paddleLeft);
		draw(paddleRight);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context

	delete (ball);
	delete (paddleLeft);
	delete (paddleRight);
	//--------------------------------------------------------------------------------------

	return 0;
}
