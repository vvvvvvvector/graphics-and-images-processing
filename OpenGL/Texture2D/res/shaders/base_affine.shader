#shader vertex
#version 330 core

uniform float value;

layout (location = 0) in vec4 vertices_position;
layout (location = 1) in vec4 colors_array;

out vec4 vertex_color;

mat4 rotate_z = mat4(cos(value), -sin(value), 0.0, 0.0,  
                  sin(value), cos(value), 0.0, 0.0,  
                  0.0, 0.0, 1.0, 0.0,  
                  0.0, 0.0, 0.0, 1.0); 

mat4 rotate_y = mat4(cos(value), 0.0, sin(value), 0.0,  
                  0.0, 1.0, 0.0, 0.0,  
                  -sin(value), 0.0, cos(value), 0.0,  
                  0.0, 0.0, 0.0, 1.0); 

mat4 rotate_x = mat4(1.0, 0.0, 0.0, 0.0,  
                  0.0, cos(value), -sin(value), 0.0,  
                  0.0, sin(value), cos(value), 0.0,  
                  0.0, 0.0, 0.0, 1.0); 
                                  
void main()
{
    gl_Position = rotate_x * rotate_y * rotate_z * vertices_position;
    vertex_color = colors_array;
}

#shader fragment
#version 330 core

in vec4 vertex_color;              
out vec4 pixel_color;
                                    
void main()
{
    pixel_color = vertex_color;
}