#version 330 core

in vec4 vertexColor;
in vec2 UV;
out vec4 color;

uniform vec3 objectColor;

void main(){

	color = vec4(objectColor.x, objectColor.y, objectColor.z , 1.0f);

}