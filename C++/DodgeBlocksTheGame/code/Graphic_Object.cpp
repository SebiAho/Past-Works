#include "Graphic_Object.h"

Graphic_Object::Graphic_Object() : loc_y(0), loc_x(0), loc_z(0), rotation(0)
{
	vertex_buffer = new GLuint;
	index_buffer = new GLuint;
	texture_buffer = new GLuint;
	texture_index_buffer = new GLuint;
}

Graphic_Object::~Graphic_Object()
{
	delete vertex_buffer, index_buffer, texture_buffer, texture_index_buffer;
}

void Graphic_Object::Move(float _x, float _y, float _z)
{
	loc_y = _y;
	loc_x = _x;
	loc_z = _z;
}