#pragma once
#include "drawable.h"
#include "gl_core_4_3.hpp"

class VBOCube : public Drawable
{
private:
	unsigned int vaoHandle; //Holds the position of the VAO
	int faces; //Contains the number of faces the shape has
public:
	GLuint textureID; //Contains the location of the cubemap texture
	VBOCube(float fvert); //Default constructor
	void render() const; //Renders the cube
	
	

};