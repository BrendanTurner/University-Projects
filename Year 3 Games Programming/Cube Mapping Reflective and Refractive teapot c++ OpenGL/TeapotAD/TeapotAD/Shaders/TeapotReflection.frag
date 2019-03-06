#version 430

out vec4 colour;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
	vec3 cameraDirection = normalize(Position - cameraPos);
	vec3 reflectVector = reflect(cameraDirection, normalize(Normal));
	colour = vec4(texture(skybox, reflectVector).rgb, 1.0);
}