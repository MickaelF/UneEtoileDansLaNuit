#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    //gl_Position = vec4(pos, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}