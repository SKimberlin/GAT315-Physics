#pragma once
#include <raylib.h>

typedef struct Body
{

	Vector2 position;
	Vector2 velocity;
	Vector2 force;

	struct Body* prev;
	struct Body* next;

} Body;