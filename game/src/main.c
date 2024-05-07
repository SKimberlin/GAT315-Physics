#include "body.h"
#include "world.h"
#include "mathf.h"
#include "force.h"
#include "integrator.h"

#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void Firework1(Vector2 position, int firework)
{
	switch (firework)
	{
	case 1:
		for (int i = 0; i < 50; i++)
		{
			ncBody* body = CreateBody();
			body->position = position;
			body->mass = GetRandomFloatValue(1, 5);
			body->inverseMass = 1 / body->mass;
			body->color = RED;
			body->type = BT_DYNAMIC;
			body->damping = 0.99f;
			body->gravityScale = body->mass;
			ApplyForce(body, (Vector2) { GetRandomFloatValue(-400, 400), GetRandomFloatValue(-400, 400) }, FM_VELOCITY);
		}
		break;
	case 2:
		for (int i = 0; i < 50; i++)
		{
			float angle = (360.0f / 50) * i;
			float radians = DEG2RAD * angle;

			float x = position.x + 100 * cosf(radians);
			float y = position.y + 100 * sinf(radians);

			ncBody* body = CreateBody();
			body->position = (Vector2){ x, y };
			body->mass = 5;
			body->inverseMass = 1 / body->mass;
			body->color = WHITE;
			body->type = BT_DYNAMIC;
			body->damping = 0.99f;
			body->gravityScale = body->mass;

			Vector2 forceDirection = Vector2Subtract(body->position, position);
			Vector2Normalize(forceDirection);
			Vector2 force = Vector2Scale(forceDirection, 3);

			ApplyForce(body, force, FM_VELOCITY);
		}
		break;
	case 3:
		for (int i = 0; i < 50; i++)
		{
			ncBody* body = CreateBody();
			body->position = position;
			body->mass = GetRandomFloatValue(2, 7);
			body->inverseMass = 1 / body->mass;
			body->color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
			body->type = BT_DYNAMIC;
			body->damping = 0.99f;
			body->gravityScale = body->mass;

			ApplyForce(body, (Vector2) { GetRandomFloatValue(-200, 200), GetRandomFloatValue(-400, -1000) }, FM_VELOCITY);
		}
		break;
	case 4:
		break;
	case 5:
		break;
	}
	
}

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Engine");
	SetTargetFPS(60);
	int fireworkSelect = 1;
	
	// initialize world
	ncGravity = (Vector2){ 0, 98 };

	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonPressed(0)) 
		{
			Firework1(position, fireworkSelect);
		}
		if (IsKeyPressed(KEY_ONE)) fireworkSelect = 1;
		if (IsKeyPressed(KEY_TWO)) fireworkSelect = 2;
		if (IsKeyPressed(KEY_THREE)) fireworkSelect = 3;
		if (IsKeyPressed(KEY_FOUR)) fireworkSelect = 4;
		if (IsKeyPressed(KEY_FIVE)) fireworkSelect = 5;

		// apply force
		//ApplyGravitation(ncBodies, 30);

		// update bodies

		ncBody* currentBody = ncBodies;
		while (currentBody)
		{
			ncBody* temp = currentBody->next;
			Step(currentBody, dt);
			if (currentBody->position.x < 0 || currentBody->position.x > SCREEN_WIDTH || currentBody->position.y < 0 || currentBody->position.y > SCREEN_HEIGHT) DestroyBody(currentBody);
			currentBody = temp;
		}

		// render
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);
		DrawText(TextFormat("BODIES: %i", ncBodyCount), 10, 50, 20, LIME);
		DrawText(TextFormat("Current Firework: %i", fireworkSelect), 10, 70, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 10, YELLOW);

		// draw bodies
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			for (int i = 0; i < body->trailLength - 1; ++i)
			{
				DrawLineEx(body->trail[i], body->trail[i + 1], 2, Fade(body->color, 0.5f));
			}

			if (body->trailLength < 50)
			{
				body->trail[body->trailLength++] = body->position;
			}
			else
			{
				for (int i = 0; i < body->trailLength - 1; ++i)
				{
					body->trail[i] = body->trail[i + 1];
				}
				body->trail[body->trailLength - 1] = body->position;
			}

			DrawCircle((int)body->position.x, (int)body->position.y, body->mass, body->color);
		}

		EndDrawing();
	}
	CloseWindow();

	ncBody* currentBody = ncBodies;
	while (currentBody)
	{
		ncBody* temp = currentBody->next;
		DestroyBody(currentBody);
		currentBody = temp;
	}

	return 0;
}