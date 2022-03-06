#version 330 core
layout (location = 0) in vec3 a_pos; // the position variable has attribute position 0
layout (location = 1) in vec3 a_color; // the position variable has attribute position 0
layout (location = 2) in vec2 a_tex_coord; // the position variable has attribute position 0  

out vec3 vertex_color;
out vec2 tex_coord;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    vertex_color = a_color;
    tex_coord = a_tex_coord;
}