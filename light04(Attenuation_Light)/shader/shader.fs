#version 410 core

struct Material {
	vec3	ambient;
	sampler2D	diffuse;
	sampler2D	specular;
	float	shineness;
};

struct Light {
	vec3	position;
	// vec3	direction;
	// vec3	color;

	vec3	ambient;
	vec3	diffuse;
	vec3	specular;

	float	constant;
	float	linear;
	float	quadratic;
};

in vec3		fragPos;
in vec3		normal;
in vec2		TexCoord;

out vec4	fragcolor;

uniform vec3	viewPos;
uniform Material	material;
uniform Light	light;

void main()
{
	float	ambientStrength = 0.1;
	vec3	ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	vec3	norm = normalize(normal);
	vec3	lightDir = normalize(light.position - fragPos);
	// vec3	lightDir = normalize(-light.direction);
	float	diff = max(dot(norm, lightDir), 0.0);
	vec3	diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	vec3	viewDir = normalize(viewPos - fragPos);
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineness);
	vec3	specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
	
	float	distance    = length(light.position - fragPos);
	float	attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

	vec3	result = (ambient + diffuse + specular) * attenuation;
	fragcolor = vec4(result, 1.0);
}
