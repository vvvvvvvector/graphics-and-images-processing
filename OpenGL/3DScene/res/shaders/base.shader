#shader vertex
#version 330 core

uniform mat4 ProjMat;
uniform mat4 ViewMat;
uniform mat4 ModelMat;

layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec4 colors_array;

out vec4 vertex_color;

void main()
{
    gl_Position = ProjMat * ViewMat * ModelMat * vertex_position;
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