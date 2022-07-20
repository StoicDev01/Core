#version 330 core

layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec2 in_texture_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//uniform mat4 model_view_projection_matrix;
out vec2 texture_coord;

void main(){
    texture_coord = in_texture_coord;

    // multiplication from right to left
    gl_Position = projection * view * model * vec4(vertex_position_modelspace, 1.0);
}