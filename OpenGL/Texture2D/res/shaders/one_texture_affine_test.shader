#shader vertex
#version 330 core

uniform float value;

layout (location = 0) in vec4 vertices_position;
layout (location = 7) in vec2 texture_coordinates; 

out vec2 v_texture_coordinates;

// mat4 MVMat = mat4(value, 0.0, 0.0, 0.0,  
//                   0.0, value, 0.0, 0.0,  
//                   0.0, 0.0, value, 0.0,  
//                   0.0, 0.0, 0.0, 1.0); 

// mat4 MVMat = mat4(cos(value), -sin(value), 0.0, 0.0,  
//                   sin(value), cos(value), 0.0, 0.0,  
//                   0.0, 0.0, 1.0, 0.0,  
//                   0.0, 0.0, 0.0, 1.0); 

// mat4 MVMat = mat4(cos(value), 0.0, sin(value), 0.0,  
//                   0.0, 1.0, 0.0, 0.0,  
//                   -sin(value), 0.0, cos(value), 0.0,  
//                   0.0, 0.0, 0.0, 1.0); 

mat4 MVMat = mat4(1.0, 0.0, 0.0, 0.0,  
                  0.0, cos(value), -sin(value), 0.0,  
                  0.0, sin(value), cos(value), 0.0,  
                  0.0, 0.0, 0.0, 1.0); 

void main()
{
    gl_Position = MVMat * vertices_position;
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