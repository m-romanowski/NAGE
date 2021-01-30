#version 450 core

layout (location = 0) in vec3 inPosition;

uniform mat4 projection;
uniform mat4 view;

out vec3 fragmentPosition;

void main()
{
    // We don't need to multiply by `model` matrix.
    // We need that because we don't let get close to the edge of skybox.
    // Player will be always in the center of skybox - skybox will be not move with the camera.
    vec4 position = projection * view * vec4(inPosition, 1.0);
    fragmentPosition = inPosition;
    gl_Position = position.xyww;
}
