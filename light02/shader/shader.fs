#version 410 core

struct Material {
	vec3	ambient;
	sampler2D	diffuse;
	sampler2D	specular;
	float	shineness;
};
uniform Material	material;

struct Light {
	vec3	position;
	vec3	color;

	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
};
uniform Light	light;

in vec2		TexCoord;

in vec3		fragPos;
in vec3		normal;

out vec4	fragcolor;

uniform vec3	objectColor;

uniform vec3	viewPos;

void main()
{
	float	ambientStrength = 0.1;
	vec3	ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	vec3	norm = normalize(normal);
	vec3	lightDir = normalize(light.position - fragPos);
	float	diff = max(dot(norm, lightDir), 0.0);
	vec3	diffuse = diff * light.color * vec3(texture(material.diffuse, TexCoord)) * light.diffuse;

	vec3	viewDir = normalize(viewPos - fragPos);
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineness);
	vec3	specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	vec3	result = (ambient + diffuse + specular) * objectColor;
	fragcolor = vec4(result, 1.0);
}
