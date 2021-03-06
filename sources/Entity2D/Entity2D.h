#ifndef __ENTITY2D__H__SL
#define __ENTITY2D__H__SL

#include <raylib.h>
// All subclasses needs to include the header of its superclass
#include "Object.h"

// Expose a pointer that will be used as the class name
extern const void * Entity2D;

// Describe all the methods you wish to expose to the world
// Setters
void set_position(void * self, int newX, int newY);
void move(void * self, int dx, int dy);
// Getters
int get_x(const void * self);
int get_y(const void * self);
Color get_color(const void * self);
// Dynamics
void draw(const void * self);

// An init method is needed because we need to set up the class before we use
// it for the first time. In our program we can create something like an initOOC
// method that will handle all these inits for us.
void initEntity2D(void);

// Expose the Entity2D class descriptor
extern const void * Entity2DClass;

#endif /* !__ENTITY2D__H__SL */
