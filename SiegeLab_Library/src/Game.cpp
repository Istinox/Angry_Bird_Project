#include "pch.h"
#include "framework.h"

#include "Game.h"
#include <ObjectPool.h>

#include "raylib.h"


void Game::Run()
{
	Camera3D camera = { 0 };
	camera.position = Vector3{ 0.0f, 10.0f, 10.0f }; 
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };     
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };    
	camera.fovy = 45.0f;                     
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

	SetTargetFPS(60);

	//----------------------------------------------------------------------------------
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
		DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
		DrawGrid(10, 1.0f);
		EndMode3D();

		DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);
		DrawFPS(10, 10);

		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
}
