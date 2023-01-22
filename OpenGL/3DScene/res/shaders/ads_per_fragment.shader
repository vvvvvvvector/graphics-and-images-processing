#shader vertex
#version 330 core

uniform mat4 ProjMat;
uniform mat4 ViewMat;
uniform mat4 ModelMat;

uniform vec3 LightPosition;
uniform vec4 LightColor;
uniform vec4 MaterialColor;

layout (location = 0) in vec4 vertex_position;
layout (location = 2) in vec3 vertex_normal;

out vec3 vertex_in_eye;
out vec3 normal;
out vec4 v_pixel_color;

void main()
{
    vertex_in_eye = (ViewMat * ModelMat * vertex_position).xyz;
    
    normal = mat3(ViewMat * ModelMat) * vertex_normal; 

    gl_Position = ProjMat * vec4(vertex_in_eye, 1.0f);
}

#shader fragment
#version 330 core

uniform vec3 LightPosition;
uniform vec4 LightColor;
uniform vec4 MaterialColor;

in vec3 vertex_in_eye;
in vec3 normal;

out vec4 pixel_color;

void main()
{
    vec3 light = normalize(LightPosition - vertex_in_eye); 

    vec3 r = reflect(-light, normal);
    vec3 e = normalize(-vertex_in_eye);

    float diffuse = max(0.0f, dot(normal, light));
    float specular = pow(max(0.0, dot(r, e)), 50);
    
    pixel_color = diffuse * MaterialColor + specular * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}