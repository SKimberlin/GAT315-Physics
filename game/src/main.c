#include "body.h"
#include "world.h"
#include "mathf.h"
#include "force.h"
#include "integrator.h"
#include "render.h"
#include "editor.h"

#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);
	
	// initialize world
	ncGravity = (Vector2){ 0, -50 };

	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 mousePosition = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom += Clamp(ncScreenZoom, 0.1f, 10);

		UpdateEditor(mousePosition);

		if (IsMouseButtonPressed(0)) 
		{
			ncBody* body = CreateBody(ConvertScreenToWorld(mousePosition), ncEditorData.massMinValue, ncEditorData.bodyTypeActive);
			body->color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
			body->damping = ncEditorData.dampingValue;
			body->gravityScale = ncEditorData.gravityScaleValue;
			AddBody(body);
		}

		// apply force
		ApplyGravitation(ncBodies, ncEditorData.gravitationValue);

		// update bodies

		for (ncBody* body = ncBodies; body; body = body->next)
		{
			Step(body, dt);
		}

		// render
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);
		DrawText(TextFormat("BODIES: %i", ncBodyCount), 10, 50, 20, LIME);


		// draw bodies
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, body->mass, body->color);
		}
		DrawEditor(mousePosition);

		EndDrawing();
	}
	CloseWindow();

	DestroyAllBodies();

	return 0;
}