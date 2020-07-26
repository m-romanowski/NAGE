#version 450 core

layout (location = 0) in vec3 inPosition;

uniform mat4 projection;
uniform mat4 view;

out vec3 textureCoords;

void main()
{
    textureCoords = inPosition;
    vec4 position = projection * view * vec4(inPosition, 1.0);
    gl_Position = position.xyww;
}
