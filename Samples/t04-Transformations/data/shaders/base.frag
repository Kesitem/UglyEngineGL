#version 330 core
out vec4 FragColor;
  
in vec2 oi_tex_coord;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
    FragColor = mix(texture(u_texture1, oi_tex_coord), texture(u_texture2, oi_tex_coord), 0.4);
}