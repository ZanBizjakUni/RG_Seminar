#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normModel;
uniform vec3 worldSpace;

void main()
{
    vec3 cameraRight = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 cameraUp = vec3(view[0][1], view[1][1], view[2][1]);
    vec3 pos = worldSpace+ cameraRight * aPos.x + vec3(0.0, 1.0f, 0.0) * aPos.y;
    gl_Position = projection * view * vec4(pos.x, pos.y, pos.z, 1.0);
    TexCoord = aTexCoord;
    Normal = normModel * aNormal; 
    FragPos = vec3(model * vec4(pos, 1.0));
}