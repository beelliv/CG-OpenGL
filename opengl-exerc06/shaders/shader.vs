#version 330

layout (location=0) in vec3 position;
layout (location=1) in vec3 color;

uniform float trans;

out vec3 colorIn;

void main(void)
{
	gl_Position = vec4(position.x + trans, position.y, position.z, 1.0);
	colorIn = color;
} 
