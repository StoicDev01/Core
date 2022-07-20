#version 330 core
out vec4 color;

in vec3 vertex_color;
in vec2 texture_coord;

uniform sampler2D texture_;

void main(){
    color = texture(texture_, texture_coord);
}