#pragma once
#include "gl_core_4_3.hpp"
#include"Texture.h"
#include <glfw3.h>
#include "scene.h"
#include "glslprogram.h"

#include"vbocube.h"
#include"vboteapot.h"

#include <glm.hpp>
using namespace imat3111;

class CubeMapScene : public Scene
{
private:
	VBOCube * skyboxCube; //cube VBO

	VBOTeapot *teapot; //Teapot VBO
	GLSLProgram teapotShaderReflect; //Contains the reflect shader for the teapot
	GLSLProgram teapotShaderRefract; //Contains the reflect shader for the teapot
	GLSLProgram skyShader; //Contains the shader for the cube map

	int width, height;

	mat4 model; //Model matrix

	Texture* glTexture;
	GLuint programHandle;

	void setMatrices(QuatCamera camera, GLSLProgram* Shader); //set the camera matrices

	void compileAndLinkShader(); //compile and link the shader

public:
	CubeMapScene(); //Constructor

	void setLightParams(QuatCamera camera, GLSLProgram* Shader); //setup the lighting

	void initScene(QuatCamera camera); //Initialise the scene

	void update(float t); //Update the scene

	void render(QuatCamera camera); //render the scene

	void resize(QuatCamera camera, int, int); //resize

};
