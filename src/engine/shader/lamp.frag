#version 450 core

out vec4 outFragmentColor;
uniform vec3 color;

void main()
{
    outFragmentColor = vec4(color, 1.0f);
}
