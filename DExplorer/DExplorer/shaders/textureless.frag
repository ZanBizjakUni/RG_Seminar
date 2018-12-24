#version 410 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3[64] lightPos;
uniform int arrSize;
uniform vec3 viewPos;

void main(){
      vec3 norm = normalize(Normal);
      float ambientStr = 0.15f;
      vec3 ambient = ambientStr * lightColor;
      float lightRad = 4.0f;
      vec3 diffSpec = vec3(0.0f, 0.0f, 0.0f);
      float specularStr = 0.5f;
      for(int i = 0; i < arrSize; i++){
            float dist = max( 1 - (distance(FragPos, lightPos[i]) / lightRad) , 0.0);
            
            vec3 lightDir = normalize(lightPos[i] - FragPos);
            float diff = max(dot(norm, lightDir), 0.0f);
            vec3 diffuse = diff * lightColor;
      //      diffuse *= dist;

            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
            vec3 specular = specularStr * spec * lightColor;
         //   specular *= dist;
            diffSpec += diffuse + specular;
      }
    //  diffSpec = vec3(min(diffSpec.x, 1.0f), min(diffSpec.y, 1.0f), min(diffSpec.z, 1.0f) );
      vec3 result = (ambient + diffSpec) * objectColor;
      FragColor = vec4(result, 1.0f);

}