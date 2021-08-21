#version 330

out vec4 FragColor;

in vec3 vcolor; //mesmo nome da variável definina no vertex shader

void main(void)
{	
	FragColor = vec4(vcolor, 1.0);
}

