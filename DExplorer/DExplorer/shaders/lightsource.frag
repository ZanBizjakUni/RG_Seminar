#version 410 core

out vec4 FragColor;

uniform vec3 lightColor;
uniform int selected;
void main(){
     vec3 result;

     if(selected == 1){
            result -= vec3(0.0f, 1.0f, 1.0f);
      }
    FragColor = vec4(lightColor + result, 1.0);

}