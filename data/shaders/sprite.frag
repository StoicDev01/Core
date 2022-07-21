#version 330 core

in vec2 tex_coord;
out vec4 color;

uniform sampler2D texture_;

void main(){
    color = texture(texture_, tex_coord);
}