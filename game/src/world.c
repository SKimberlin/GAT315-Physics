#include "world.h"
#include <assert.h>
#include <stdlib.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody()
{
	Body* body = (Body*)malloc(sizeof(Body));
	assert(body);
	body->prev = NULL;
	body->next = bodies;
	if (bodies) bodies->prev = body;
	bodies = body;
	bodyCount++;
	return body;
}

void DestroyBody(Body* body)
{
	assert(body);
	if (body->prev) body->next = body->prev;
	if (body->next) body->prev = body->next;
	if (body == bodies) bodies = body->next;
	bodyCount--;
	free(body);
}
