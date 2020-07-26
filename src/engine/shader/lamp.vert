#version 450 core

layout (location = 0) in vec3 inPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Result: Matrix4 = MVP(Projection * View * Model)
    vec4 position = projection * view * model * vec4(inPosition, 1.0f);
    gl_Position = position;
}
