#version 330 core

out vec4 fragcolor;

in vec4 color;
in vec2 TexCoord;

uniform float mixVal;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	fragcolor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), mixVal);
}
