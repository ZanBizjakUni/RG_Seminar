#version 410 core

#define MAX_LIGHTS 32

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3[MAX_LIGHTS] lightPos;
uniform int arrSize;

void main(){
      vec3 norm = normalize(Normal);
      float ambientStr = 0.15f;
      vec3 ambient = ambientStr * lightColor;
      float lightRad = 4.0f;
      vec3 diffSpec = vec3(0.0f, 0.0f, 0.0f);
      float specularStr = 0.5f;
      float dist;
      vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);
      int foo = arrSize;
      for(int i = 0; i < MAX_LIGHTS; i++){
            
            dist = max( 1 - (distance(FragPos, lightPos[i]) / lightRad) , 0.0);
            
            vec3 lightDir = normalize(lightPos[i] - FragPos);
            float diff = max(dot(norm, lightDir), 0.0f);
            vec3 diffuse = diff * lightColor;
            diffuse *= dist;
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
            vec3 specular = specularStr * spec * lightColor;
            specular *= dist;
            diffSpec += diffuse + specular;
      }
    diffSpec = vec3(min(diffSpec.x, 1.0f), min(diffSpec.y, 1.0f), min(diffSpec.z, 1.0f) );

    result = vec4((ambient + (diffSpec)), 1.0f) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

    FragColor = result;

}

/*
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
    
      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(lightPos - FragPos);
      float diff = max(dot(norm, lightDir), 0.0f);
      vec3 diffuse = diff * lightColor;


      float ambientStr = 0.15f;
      vec3 ambient = ambientStr * lightColor;

      float specularStr = 0.5f;
      vec3 viewDir = normalize(viewPos - FragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
      vec3 specular = specularStr * spec * lightColor;

      vec3 result = (ambient + diffuse + specular) * objectColor;
      FragColor = vec4(result, 1.0f);

}
*/