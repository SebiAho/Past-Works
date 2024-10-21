#pragma once

#include <vector>
#include <GLES2/gl2.h>
#include "glm/glm.hpp"

struct GTexture{
	GLuint id;
	int width;
	int height;
};

class Graphic_Object//Use for holding data and functions about a drawable object
{
public:
	Graphic_Object();
	~Graphic_Object();

	unsigned int vertex_amount, index_amount, texture_amount, texture_index_amount;
	GLuint *vertex_buffer, *index_buffer, *texture_buffer, *texture_index_buffer;

	void Move(float _x, float _y , float _z);
	
	glm::vec3 getPosition(){ return glm::vec3(loc_y, loc_x, loc_z); };

private:
	float loc_y, loc_x, loc_z, rotation;

};