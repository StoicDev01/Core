#version 330 core
out vec4 color;
in vec2 texture_coord;

uniform sampler2D texture_;

void main(){
    color = texture(texture_, texture_coord);
    //color = vec4(1,0,0,1);
}