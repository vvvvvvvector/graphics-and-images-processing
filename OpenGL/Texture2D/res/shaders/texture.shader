#shader vertex
#version 330 core

layout (location = 0) in vec4 vertices_position;
layout (location = 7) in vec2 textureCoords; 

out vec2 v_TexCoord;

void main()
{
    gl_Position = vertices_position;
    v_TexCoord = textureCoords;
}

#shader fragment
#version 330 core

uniform sampler2D SamplerTex; 

in vec2 v_TexCoord;

out vec4 pixel_color;

void main()
{
    pixel_color = texture(SamplerTex, v_TexCoord);
}