#version 460 core
layout (location = 0) in vec2 vertex;

uniform mat4 model;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * model * vec4(vertex, 0.0, 1.0);
}