#version 410 core

struct Material {
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
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

in vec3		fragPos;
in vec3		normal;

out vec4	fragcolor;

uniform vec3	objectColor;

uniform vec3	viewPos;

void main()
{
	float	ambientStrength = 0.1;
	vec3	ambient = light.ambient * material.ambient * light.color;

	vec3	norm = normalize(normal);
	vec3	lightDir = normalize(light.position - fragPos);
	vec3	diffuse = max(dot(norm, lightDir), 0.0) * light.color * material.diffuse * light.diffuse;

	float	specularStrength = 0.5;
	vec3	viewDir = normalize(viewPos - fragPos);
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineness);
	vec3	specular = specularStrength * spec * light.color * material.shineness * light.specular;

	vec3	result = (ambient + diffuse + specular) * objectColor;
	fragcolor = vec4(result, 1.0);
}
