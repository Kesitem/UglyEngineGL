#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 texCoord;

uniform float texture_scale;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    texCoord = aTexCoord;

    if(texture_scale < 1.0)
    {
        if(texCoord.x == 0)
            texCoord.x = 0.5 - (texture_scale / 2);
        else
            texCoord.x = 0.5 + (texture_scale / 2);

        if(texCoord.y == 0)
            texCoord.y = 0.5 - (texture_scale / 2);
        else
            texCoord.y = 0.5 + (texture_scale / 2);
    }
    else
    {
        if(texCoord.x > 0)
            texCoord.x = texture_scale;

        if(texCoord.y > 0)
            texCoord.y = texture_scale;
    }
    
}