#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;

uniform float u_offset;

out vec4 o_vertex_color;

void main()
{
    gl_Position = vec4(a_pos.x + u_offset, a_pos.y, a_pos.z, 1.0);
    o_vertex_color = vec4(a_color, 1.0);
}