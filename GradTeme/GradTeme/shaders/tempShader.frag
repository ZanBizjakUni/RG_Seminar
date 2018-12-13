#version 330 core

out vec4 color;
in vec2 UV;

uniform sampler2D ourSampler;
uniform int damaged;

void main(){

	color = texture(ourSampler, UV);
	if (damaged == 1){
		color = color + vec4(0.3f, 0.0f, 0.0f, 1.0f);
	}
	
}