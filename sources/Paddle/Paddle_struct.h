#pragma once

#include "Entity2D_struct.h"

struct Paddle
{
	const struct Entity2D _;
	int w;
	int h;
};

struct PaddleClass
{
	const struct Entity2DClass _;

	void (*draw)(const void * self);
};

void super_draw(const void * class, const void * self);

