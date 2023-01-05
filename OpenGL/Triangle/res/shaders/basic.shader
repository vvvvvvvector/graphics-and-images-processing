#shader vertex
#version 330 core

layout (location = 0) in vec4 trianglePos;
                                  
void main()
{
    gl_Position = trianglePos;
}

#shader fragment
#version 330 core
                                    
out vec4 fragColor;
                                    
void main()
{
     fragColor = vec4(0.2, 0.3, 0.8, 1.0);
}