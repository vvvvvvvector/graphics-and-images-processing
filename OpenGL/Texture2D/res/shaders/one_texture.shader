#shader vertex
#version 330 core

layout (location = 0) in vec4 vertices_position;
layout (location = 7) in vec2 texture_coordinates; 

out vec2 v_texture_coordinates;

void main()
{
    gl_Position = vertices_position;
    v_texture_coordinates = texture_coordinates;
}

#shader fragment
#version 330 core

uniform sampler2D texture_1; 

in vec2 v_texture_coordinates;

out vec4 pixel_color;

void main()
{
    pixel_color = texture(texture_1, v_texture_coordinates);
}