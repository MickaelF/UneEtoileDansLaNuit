#version 300 es
out highp vec4 FragColor;

in highp vec2 TexCoord;

uniform sampler2D ourTexture;
uniform mediump vec4 color;

void main()
{
    FragColor = color;
}