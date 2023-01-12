#shader vertex
#version 330 core

layout (location = 0) in vec4 vertices_position;
layout (location = 7) in vec2 texture_coords; 

out vec2 v_texture_coords;

void main()
{
    gl_Position = vertices_position;
    v_texture_coords = texture_coords;
}

#shader fragment
#version 330 core

uniform sampler2D texture_1; 
uniform sampler2D texture_2; 

in vec2 v_texture_coords;

out vec4 pixel_color;

void main()
{
    pixel_color = mix(texture(texture_1, v_texture_coords), texture(texture_2, v_texture_coords), 0.6);
}