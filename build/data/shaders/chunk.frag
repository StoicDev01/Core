uniform sampler2D texture;
uniform sampler2D depth_texture;
uniform int chunk_size;

varying vec4 vertex;

vec4 colorLerp(float x,vec4 color1, vec4 color2){
   return (color2 - color1) * x + color1;
}


void main()
{
   // lookup the pixel in the texture
   vec4 texture_pixel = texture2D(texture, gl_TexCoord[0].xy);
   vec4 chunk_position = floor(vertex / vec4(chunk_size * 32, chunk_size * 32, 0, 0));
   vec4 cell_pos = floor(vertex / 32);
   vec4 chunk_cell_pos = floor((cell_pos) - (chunk_position  * chunk_size) );
   vec4 current_obj_distance = texture2D(depth_texture, vec2(1,1));

   //vec4 pixel = colorLerp(current_obj_distance.x, texture_pixel, vec4(0, 0, 1, 255) );

   vec4 pixel = current_obj_distance;

   gl_FragColor = texture_pixel;
}