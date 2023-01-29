#shader vertex
#version 330 core

uniform mat4 ProjMat;
uniform mat4 ViewMat;
uniform mat4 ModelMat;
uniform float angle;

float value = sin(angle) * sin(-angle) * cos(angle);

layout (location = 0) in vec4 vertex_position;
layout (location = 7) in vec2 texture_coords; 

out vec2 v_texture_coords;

void main()
{
    vec3 pos = vertex_position.xyz;

    if (pos.y > 0) pos.z += value;

    gl_Position =  ProjMat * ViewMat * ModelMat * vec4(pos, 1.0);
    v_texture_coords = texture_coords;
}

#shader fragment
#version 330 core

uniform sampler2D grass_texture; 

in vec2 v_texture_coords;

out vec4 fragment_color;

void main()
{
    vec4 texture_color = texture(grass_texture, v_texture_coords);

    if (texture_color.a < 0.05) discard;

    fragment_color = texture_color;
}