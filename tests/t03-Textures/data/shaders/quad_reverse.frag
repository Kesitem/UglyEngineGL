#version 330 core

out vec4 FragColor;
  
in vec2 tex_coord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    FragColor = mix(
        texture(texture0, tex_coord), 
        texture(texture1, vec2(1 - tex_coord.x, tex_coord.y)), 
        0.2);
}