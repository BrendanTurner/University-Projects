#include "vbocube.h"
#include<string>
#include"Bitmap.h"

VBOCube::VBOCube(float fvert)
{
	faces = 6;
	float vertices[] =
	{
		-fvert, -fvert, -fvert, //V0 back bottom left
		-fvert,  fvert, -fvert, //V1 back top left
		 fvert,  fvert, -fvert, //V2 back top right
		 fvert, -fvert, -fvert, //V3 back bottom right

		-fvert, -fvert,  fvert, //V4 front bottom left
		-fvert,  fvert,  fvert, //V5 front top left
		 fvert,  fvert,  fvert, //V6 front top right
		 fvert, -fvert,  fvert  //V7 front bottom right
	}; //Vertex array

	GLuint indices[] =
	{
		0,1,2,//front
		0,2,3,

		7,6,5,//back
		7,5,4,

		1,5,6,//top
		1,6,2,

		4,0,3,//bottom
		4,3,7,

		4,5,1,//left
		4,1,0,

		3,2,6,//right
		3,6,7
	};

	gl::GenTextures(1, &textureID);
	gl::BindTexture(gl::TEXTURE_CUBE_MAP, textureID);

	GLuint CubeFaces[6] =
	{
		gl::TEXTURE_CUBE_MAP_POSITIVE_X, //RIGHT
		gl::TEXTURE_CUBE_MAP_NEGATIVE_X, //LEFT
		gl::TEXTURE_CUBE_MAP_POSITIVE_Y, //TOP
		gl::TEXTURE_CUBE_MAP_NEGATIVE_Y, //Bottom
		gl::TEXTURE_CUBE_MAP_POSITIVE_Z, //BACK
		gl::TEXTURE_CUBE_MAP_NEGATIVE_Z //FRONT
	};

	//for every face of the cubemap
	for (int i = 0; i < faces; i++)
	{
		std::string TextureDir = "Images/cubemap/" + std::to_string(i) + ".jpg";//set the directory to search
		Bitmap bmp = Bitmap::bitmapFromFile(TextureDir); //load the bitmap from the directory
		gl::TexImage2D(CubeFaces[i],				//apply the texture to this face
			0,
			gl::RGB,						//the colour format used for the image
			bmp.width(),					//make the bitmap this width
			bmp.height(),					//make the bitmap this height
			0,
			gl::RGB,						//the colour format used for this image
			gl::UNSIGNED_BYTE,
			bmp.pixelBuffer());				//use these colour bits for the face
	}

	//sets the parameter for the cube map
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);

	GLuint handle[2];
	gl::GenBuffers(2, handle);

	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertices), vertices, gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(0);  // Vertex position

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, handle[1]);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, 6 * faces * sizeof(unsigned int), indices, gl::STATIC_DRAW);/////start here

	gl::BindVertexArray(0);
}

void VBOCube::render() const
{
	gl::DepthFunc(gl::LEQUAL);

	gl::BindVertexArray(vaoHandle);//binds the VAO to be drawn

	//Draws the contents of the VAO as Triangles using the indices
	gl::DrawElements(gl::TRIANGLES, 6 * faces, gl::UNSIGNED_INT, ((GLubyte*)NULL + (0)));
}
