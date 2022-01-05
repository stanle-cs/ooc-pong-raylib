#include <assert.h>
#include <math.h>
#include <raylib.h>
// All implementation file of a new class need to include the class's struct and
// the class's header file
#include "Entity2D.h"
#include "Entity2D_struct.h"

//------------------------------------------------------------------------------
/* All the static methods. Static methods are methods that can be inherited as-
 * is and the subclasses won't need to implement their own version of these
 */

//getters

int get_x(const void * _self)
{
	const struct Entity2D * self = _self;
	assert(self);

	return self->x;
}

int get_y(const void * _self)
{
	const struct Entity2D * self = _self;
	assert(self);

	return self->y;
}

Color get_color(const void * _self)
{
	const struct Entity2D * self = _self;
	assert(self);

	return self->color;
}

//setters
void set_position(void * _self, int newX, int newY)
{
	struct Entity2D * self = _self;
	assert(self);

	self->x = newX;
	self->y = newY;
}

void move(void * _self, int dx, int dy)
{
	float force = 100.0;
	struct Entity2D * self = _self;
	assert(self);
	
	self->x = self->x + round(force*dx*GetFrameTime());
	self->y = self->y + round(force*dy*GetFrameTime());
}
//------------------------------------------------------------------------------
/* Dynamic methods. These are the selectors we create so that we can select new
 * methods created by any subclasses of this class later on.
 */

/* Make sure we have the correct "contract" when we declare the function signa-
 * ture. For example in this case, we want to modify the stuff pointed at by 
 * _self, but not the metadata in its class datastructure, so it is important 
 * that we put a const in front of the class variable but not the _self pointer.
 */
void draw(const void * _self)
{
	const struct Entity2DClass * class = class_of(_self);

	assert(class->draw);
	class->draw(_self);
}

//------------------------------------------------------------------------------
/* Superclass selectors. These selectors are used by any subclasses of this cla-
 * ss to call this class's methods. Be careful of the variable contract, make
 * sure that if the function called by the selector will modify the data, we
 * cannot contract it as a const variable.
 */
void super_draw(const void * _class,const  void * _self)
{
	const struct Entity2DClass * superclass = super(_class);

	assert(_self && superclass->draw);
	superclass->draw(_self);
}
//------------------------------------------------------------------------------
/* Class methods. These methods are actual methods that will be called by the
 * selectors defined above. Other methods that we want to overload from the sup-
 * erclass will also be defined here. A standar practice is to name these with
 * prefix ClassName_* for consistency. */

static void * Entity2D_ctor(void * _self, va_list * arglist_ptr)
{
	// First we need to chain up and let the constructor of the super class
	// do its job and create everything for us first.
	struct Entity2D * self = super_ctor(Entity2D, _self, arglist_ptr);


	// Now we do the class specific constructing. Usually it involves just
	// filling the data of the struct from the va_list given.
	self->x = va_arg(*arglist_ptr, int);
	self->y = va_arg(*arglist_ptr, int);
	self->color = va_arg(*arglist_ptr, Color);
	// Gotta return the pointer to self. This is needed for any subclasses
	// to use this ctor later when they implement their own ctor.
	return self;
}

// Here we are modifying the data pointed to by _self, therefore we need to make
// sure that we do not put a const qualifier in front of it.
static void Entity2D_draw(const void * _self)
{
	// First we cast the self pointer to the correct type
	const struct Entity2D * self = _self;

	// Then we will actually do the job here
	DrawPixel(self->x, self->y, self->color);
}
//------------------------------------------------------------------------------
// Entity2DClass methods. We don't need much, usually just a simple ctor is eno-
// ugh. We actually will just copy the entire function from the boiler plate and
// change the part where we assign methods to the pointers declared in the data
// structure.

static void * Entity2DClass_ctor(void * _self, va_list * arglist_ptr)
{
	struct Entity2DClass * self = super_ctor(Entity2DClass, _self, arglist_ptr);

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
// Initialization. The bad thing about our setup is that we need to init all the
// defined classes' datastructure before we can use them as a class. This means
// that in our main function, somewhere we need to call an init function that 
// set all of this up.

const void * Entity2DClass;
const void * Entity2D;

void initEntity2D(void)
{
	if (!Entity2DClass)
	{
		Entity2DClass = new(
				Class,
				"Entity2DClass",
				Class,
				sizeof(struct Entity2DClass),
				ctor, Entity2DClass_ctor,
				NULL);
	}
	if (!Entity2D)
	{
		Entity2D = new(
				Entity2DClass,
				"Entity2D",
				Object,
				sizeof(struct Entity2D),
				ctor, Entity2D_ctor,
				draw, Entity2D_draw,
				NULL);
	}
}
