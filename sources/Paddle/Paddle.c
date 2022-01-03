#include <assert.h>
#include <raylib.h>

#include "Paddle.h"
#include "Paddle_struct.h"

//------------------------------------------------------------------------------
//static

int get_w(const void * _self)
{
	const struct Paddle * self = _self;
	assert(self && self->w);

	return self->w;
}

int get_h(const void * _self)
{
	const struct Paddle * self = _self;
	assert(self && self->h);

	return self->h;
}

//------------------------------------------------------------------------------
//dynamic

void draw(const void * _self)
{
	const struct PaddleClass * class = class_of(_self);

	assert(class->draw);
	class->draw(_self);
}

//------------------------------------------------------------------------------
//super selector

void super_draw(const void * _class, const void * _self)
{
	const struct PaddleClass * superclass = super(_class);

	assert(_self && superclass->draw);
	superclass->draw(_self);
}

//------------------------------------------------------------------------------
//actual method

static void * Paddle_ctor(void * _self, va_list * arglist_ptr)
{
	struct Paddle * self = super_ctor(Paddle, _self, arglist_ptr);
	
	self->w = va_arg(*arglist_ptr, int);
	self->h = va_arg(*arglist_ptr, int);

	return self;
}

static void Paddle_draw(const void * _self)
{
	const struct Paddle * self = _self;

	assert(self);

	DrawRectangle(get_x(self), get_y(self), self->w, self->h, DARKGRAY);
}

//------------------------------------------------------------------------------
//class ctor

static void * PaddleClass_ctor(void * _self, va_list * arglist_ptr)
{
	struct PaddleClass * self = super_ctor(PaddleClass, _self, arglist_ptr);

	typedef void (*funcptr)();
	funcptr selector;

	va_list cpy_arglist;
	va_copy(cpy_arglist, *arglist_ptr);

	while((selector = va_arg(cpy_arglist, funcptr)))
	{
		funcptr method = va_arg(cpy_arglist, funcptr);
		// Only part we change to add methods to their resprective slots.
		if (selector == (funcptr) draw)
			*((funcptr *) &self->draw) = method;
	}
	va_end(cpy_arglist);
	
	return self;
}

//------------------------------------------------------------------------------
//Initialization

const void * Paddle;
const void * PaddleClass;

void initPaddle(void)
{
	initEntity2D();
	if (!PaddleClass)
	{
		PaddleClass = new(
				Entity2DClass,
				"PaddleClass",
				Entity2DClass,
				sizeof(struct PaddleClass),
				ctor, PaddleClass_ctor,
				NULL);
	}
	if (!Paddle)
	{
		Paddle = new(
				PaddleClass,
				"Paddle",
				Entity2D,
				sizeof(struct Paddle),
				ctor, Paddle_ctor,
				draw, Paddle_draw,
				NULL);
	}
}
