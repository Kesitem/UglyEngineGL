#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;

uniform mat4 u_transform;

out vec2 oi_tex_coord;

void main()
{
    gl_Position = u_transform * vec4(a_pos, 1.0);
    oi_tex_coord = a_tex_coord;
}