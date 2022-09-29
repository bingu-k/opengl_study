#version 410 core

in vec3		fragPos;
in vec3		normal;

out vec4	fragcolor;

uniform vec3	objectColor;
uniform vec3	lightColor;
uniform vec3	lightPos;

uniform vec3	viewPos;

void main()
{
	float	ambientStrength = 0.1;
	vec3	ambient = ambientStrength * lightColor;

	vec3	norm = normalize(normal);
	vec3	lightDir = normalize(lightPos - fragPos);
	vec3	diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

	float	specularStrength = 0.5;
	vec3	viewDir = normalize(viewPos - fragPos);
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3	specular = specularStrength * spec * lightColor;  

	vec3	result = (ambient + diffuse + specular) * objectColor;
	fragcolor = vec4(result, 1.0);
}
