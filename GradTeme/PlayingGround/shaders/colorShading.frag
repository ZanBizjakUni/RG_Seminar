#version 330 core

in vec4 vertexColor;
in vec2 UV;
out vec4 color;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main(){

	color = mix(texture(ourTexture0,UV), texture(ourTexture1, UV), 0.2);
}