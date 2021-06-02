#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 in_normal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    FragPos = vec3(model * vec4(vertex_pos, 1.0));
    Normal = mat3(transpose(inverse(model))) * in_normal;

    gl_Position = proj * view * vec4(FragPos, 1.0);
}
