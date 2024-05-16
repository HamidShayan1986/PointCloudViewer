#version 150
#extension GL_ARB_explicit_attrib_location : enable
layout(location = 0) in vec3 vertexPos;

uniform mat4 worldViewProjMat;

void main()
{
    gl_Position = worldViewProjMat * vec4(vertexPos, 1);
}
