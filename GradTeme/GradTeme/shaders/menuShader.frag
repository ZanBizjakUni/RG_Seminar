#version 330 core

out vec4 color;
in vec2 UV;

uniform sampler2D ourSampler;

void main(){

	color = texture(ourSampler, UV);
	
}