#version 410

in vec2		TexCoords;

out vec3	FragColor;

uniform sample2D	texture_diffuse1;

int main(void)
{
	FragColor = texture(texture_diffuse1, TexCoords);
};