#version 430 core

in vec3 reflection_dir;

out vec4 fcolor;

uniform samplerCube cubemap;

void main()
{
	fcolor = texture(cubemap, reflection_dir);
}
