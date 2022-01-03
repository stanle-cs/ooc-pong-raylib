#ifndef __ENTITY2D_STRUCT__H__SL
#define __ENTITY2D_STRUCT__H__SL

#include <raylib.h>
#include "Object_struct.h"

/*
 * To create a new class using the ooc system, we need to create two structures,
 * the actua object data structure and then its class structure. The object
 * structure is your normal class in other languages, while the class structure
 * will be used to hold the metadata about the class such as all its member me-
 * thods. */



// Entity2D data structure
struct Entity2D
{
	const struct Object _; // This is the superclass of this class.
	// From here down are actual data of the class
	int x;
	int y;
	Color color;
};
#define GET_X(p) (((const struct Entity2D *) (p))->x)
#define GET_Y(p) (((const struct Entity2D *) (p))->y)

// Entity2DClass class descriptor
struct Entity2DClass
{
	// this is the class descriptor, required to be at the beginning of the file
	const struct Class _; 	
	// From here down are the methods of the class
	// No need to list all the methods that are listed by the superclass
	void (*draw) (const void * self);
	
};

// For each methods defined in the Class descriptor, we need a super_* methods 
// so that subclass of this class can call it.
void super_draw(const void * class, const void * self);

#endif /* !__ENTITY2D_STRUCT__H__SL */
