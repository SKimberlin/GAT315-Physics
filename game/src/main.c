#include "body.h"
#include "world.h"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonPressed(0))
		{
			Body* body = CreateBody();
			body->position = position;
			body->velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
		}

		// render
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 10, YELLOW);

		// update & draw bodies
		Body* currentBody = bodies;
		while (currentBody)
		{
			currentBody->position = Vector2Add(currentBody->position, currentBody->velocity);
			DrawCircle((int)currentBody->position.x, (int)currentBody->position.y, 5, RED);
			currentBody = currentBody->next;
		}

		EndDrawing();
	}
	CloseWindow();
	
	Body* currentBody = bodies;
	while (currentBody)
	{
		Body* temp = currentBody->next;
		DestroyBody(currentBody);
		currentBody = temp;
	}

	return 0;
}