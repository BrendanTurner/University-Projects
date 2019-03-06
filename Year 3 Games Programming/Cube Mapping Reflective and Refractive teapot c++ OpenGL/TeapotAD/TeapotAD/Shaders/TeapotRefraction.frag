#version 430

out vec4 colour;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
	float refractRatio = 1.00/1.52;
	vec3 cameraDirection = normalize(Position - cameraPos);
	vec3 refractVector = refract(cameraDirection, normalize(Normal), refractRatio);
	colour = vec4(texture(skybox, refractVector).rgb, 1.0);
}