#version 430

layout (location = 0) in vec3 VertexPosition;

out vec3 TexCoords;

uniform mat4 View;
uniform mat4 Projection;

void main()
{

   gl_Position = Projection * View * vec4(VertexPosition, 1.0f);
   TexCoords = VertexPosition;
}
