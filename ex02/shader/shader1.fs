#version 330 core

out vec4 fragcolor;

in vec4 color;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	fragcolor = texture(texture1, TexCoord);
}
