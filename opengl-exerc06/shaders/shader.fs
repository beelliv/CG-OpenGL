#version 330
out vec4 FragColor;

in vec3 colorIn;

void main(void)
{	
	FragColor = vec4(colorIn, 1.0);
}

