#version 330 core
out vec4 FragColor;
  
in vec2 tex_coord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, tex_coord);;
}