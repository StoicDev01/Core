#version 330 core

layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec3 in_vertex_color;
layout(location = 2) in vec2 in_texture_coord;

uniform mat4 model_view_projection_matrix;
out vec3 vertex_color;
out vec2 texture_coord;

void main(){
    //gl_Position = vec4(1,0,0,1);
    gl_Position = vec4(vertex_position_modelspace, 1);

    vertex_color = in_vertex_color;
    texture_coord = in_texture_coord;
}