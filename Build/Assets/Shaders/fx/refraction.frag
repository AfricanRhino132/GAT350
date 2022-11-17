#version 430 core

in vec3 refraction_dir;

out vec4 fcolor;

uniform samplerCube cubemap;

void main()
{
	fcolor = texture(cubemap, refraction_dir);	
}
