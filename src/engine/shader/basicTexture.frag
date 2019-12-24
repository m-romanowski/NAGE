#version 450 core

uniform sampler2D textureSampler;

in vec2 textureCoords;
out vec4 fragColor;

void main()
{
    fragColor = texture(textureSampler, textureCoords);
}
