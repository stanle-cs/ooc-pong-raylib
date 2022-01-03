#ifndef __ENTITY2D__H__SL
#define __ENTITY2D__H__SL

// All subclasses needs to include the header of its superclass
#include "Object.h"

// Expose a pointer that will be used as the class name
extern const void * Entity2D;

// Describe all the methods you wish to expose to the world
void move(void * self, int dx, int dy);
int get_x(void * self);
int get_y(void * self);
// An init method is needed because we need to set up the class before we use
// it for the first time. In our program we can create something like an initOOC
// method that will handle all these inits for us.
void initEntity2D(void);

// Expose the Entity2D class descriptor
extern const void * Entity2DClass;

#endif /* !__ENTITY2D__H__SL */
