#version 450 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 textureCoords;

void main()
{
    textureCoords = inTextureCoords;
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}
