#version 300 es
layout (location = 0) in highp vec3 pos;
layout (location = 1) in highp vec3 normal;
layout (location = 2) in highp vec3 texCoord;

uniform highp mat4 modelMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;

void main()
{
    gl_Position = vec4(pos, 1.0);
    //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}