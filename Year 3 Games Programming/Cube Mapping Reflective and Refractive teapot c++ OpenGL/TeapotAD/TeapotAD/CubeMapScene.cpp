#include "CubeMapScene.h"
#include <iostream>
using std::cerr;
using std::endl;

CubeMapScene::CubeMapScene()
{
}

void CubeMapScene::setMatrices(QuatCamera camera, GLSLProgram* Shader)
{
	// make this the current shader
	Shader->use();

	//set all the uniforms for the current shader
	Shader->setUniform("Model", model);//used in the teapot projection shader
	Shader->setUniform("View", camera.view());//used in the skybox vertex shader and the teapot vertex shader
	Shader->setUniform("Projection", camera.projection());//used in the skybox vertex shader and the teapot vertex shader
	Shader->setUniform("cameraPos", camera.position());//used in the teapot reflection and refraction fragment shader
}

void CubeMapScene::compileAndLinkShader()
{
	try
	{
		//compiles both the vertex and fragment shader used for the cubemap
		skyShader.compileShader("Shaders/Skybox.vert");
		skyShader.compileShader("Shaders/Skybox.frag");
		skyShader.link();//links the compiled shaders to the GLSLProgram variable
		skyShader.validate();//validates the shader has loaded correctly
	}
	catch (GLSLProgramException & e)//if the shader failed to load then the program exits with an exception
	{
		std::cerr << e.what()<<std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		//compiles both the vertex and the fragment shader for the teapot reflection
		teapotShaderReflect.compileShader("Shaders/Teapot.vert");
		teapotShaderReflect.compileShader("Shaders/TeapotReflection.frag");
		teapotShaderReflect.link();//links the compiled shaders to the GLSLProgram variable
		teapotShaderReflect.validate();//validates the shader has loaded correctly
	}
	catch (GLSLProgramException & e)//if the shader failed to load then the program exits with an exception
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		//compiles both the vertex and the fragment shader for the teapot refraction
		teapotShaderRefract.compileShader("Shaders/Teapot.vert");
		teapotShaderRefract.compileShader("Shaders/TeapotRefraction.frag");
		teapotShaderRefract.link();//links the compiled shaders to the GLSLProgram variable
		teapotShaderRefract.validate();//validates the shader has loaded correctly
	}
	catch (GLSLProgramException & e)//if the shader failed to load then the program exits with an exception
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void CubeMapScene::initScene(QuatCamera camera)
{
	//Compile and link the shader
	compileAndLinkShader();

	gl::Enable(gl::DEPTH_TEST);

	//a matrix to move the teapot lid upwards
	glm::mat4 lid = glm::mat4(1.0);

	//create the teapot with translated lid
	teapot = new VBOTeapot(16, lid);

	//create the cube for the skybox
	skyboxCube = new VBOCube(50.0f);
}

void CubeMapScene::setLightParams(QuatCamera camera, GLSLProgram* Shader)
{
	//if lighting is used
	//set the world light position
	vec3 worldLight = vec3(10.0f, 10.0f, 10.0f);

	//send the world light colour to the shader
	Shader->setUniform("Ld", 0.9f, 0.9f, 0.9f);//diffuse
	Shader->setUniform("la", 0.3f, 0.3f, 0.3f);//ambient
	Shader->setUniform("ls", 0.3f, 0.3f, 0.3f);//specular

	//send the world light position to the shader
	Shader->setUniform("LightPosition", worldLight);
}

//not used as nothing is needed to update
void CubeMapScene::update(float t)
{

}

void CubeMapScene::render(QuatCamera camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	//Now set up the teapot 
	
	if(refOrRaf())
	{ 
		setMatrices(camera, &teapotShaderReflect);
	}
	else
	{
		setMatrices(camera, &teapotShaderRefract);
	}
	//Set the Teapot material properties in the shader and render
	gl::BindTexture(gl::TEXTURE_CUBE_MAP, skyboxCube->textureID);
	teapot->render();
	
	//set up the skybox
	setMatrices(camera, &skyShader);
	skyboxCube->render();

}

void CubeMapScene::resize(QuatCamera camera, int w, int h)
{
	gl::Viewport(0, 0, w, h);
	width = w;
	height = h;
	camera.setAspectRatio((float)w / h);

}