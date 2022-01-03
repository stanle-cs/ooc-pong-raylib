#pragma once

#include "Entity2D.h"

extern const void * Paddle;
extern const void * PaddleClass;

void draw(const void * self);
int get_w(const void * self);
int get_h(const void * self);

void initPaddle(void);

