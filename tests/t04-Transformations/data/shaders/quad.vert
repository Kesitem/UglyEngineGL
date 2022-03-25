#version 330 core
layout (location = 0) in vec3 a_pos; // the position variable has attribute position 0
layout (location = 1) in vec3 a_color; // the position variable has attribute position 0
layout (location = 2) in vec2 a_tex_coord; // the position variable has attribute position 0  

out vec2 tex_coord;

uniform mat4 u_transform;

void main()
{
    gl_Position = u_transform * vec4(a_pos, 1.0);
    tex_coord = a_tex_coord;
}