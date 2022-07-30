#version 330 core

in vec2 tex_coord;
out vec4 color;

uniform vec4 mult_color;
uniform sampler2D texture_;

void main(){
    color = mult_color;
    color *= texture(texture_, tex_coord);
    //color = vec4(1,0,0,1);
}