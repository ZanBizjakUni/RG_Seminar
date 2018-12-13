#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 UV;

out vec4 color;

uniform sampler2D ourSampler;

uniform vec3 lightColor;
uniform vec3 lightPos;
void main(){

	float ambitentStrength = 0.2f;
	vec3 ambient = ambitentStrength * lightColor;
	
	vec3 dist = vec3(distance(FragPos.x, lightPos.x), distance(FragPos.y, lightPos.z), distance(FragPos.z, lightPos.z));
	float lightIntesity = ((15.0f - (dist.x + dist.y + dist.z)) / 3.0f) * 0.8f;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	
/*	vec3 result = (ambient ) * vec3(lightIntesity);
	color = texture(ourSampler, UV) * vec4(result , 1.0f);*/
	color = texture(ourSampler, UV);

}