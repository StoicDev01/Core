varying vec4 vertex;

void main()
{
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    //gl_FrontColor = gl_Color;
    vertex = gl_Vertex;
    //gl_Color = vec4(1, 0, 0, 1);
    //gl_FrontColor = gl_Color;
}