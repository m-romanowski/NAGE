#version 450 core

uniform sampler2D textureSampler;

in vec2 textureCoords;
out vec4 fragColor;

void main()
{
    // Texture color.
    vec4 color = texture(textureSampler, textureCoords);

    // If texture alpha < 0.1 discard this fragment.
    if(color.a < 0.1)
        discard;

    fragColor = color;
}
