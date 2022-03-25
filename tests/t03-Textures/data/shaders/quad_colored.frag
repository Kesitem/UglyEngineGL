#version 330 core

out vec4 FragColor;
  
in vec3 vertex_color;
in vec2 tex_coord;

uniform sampler2D texture0;

void main()
{
    FragColor = texture(texture0, tex_coord) * vec4(vertex_color, 1.0);
}