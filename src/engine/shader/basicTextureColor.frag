#version 450 core

uniform sampler2D textureSampler;

in vec2 textureCoords;
in vec3 color;
out vec4 fragColor;

void main()
{
    // Apply texture color with additional color.
    vec4 color = texture(textureSampler, textureCoords) * vec4(color, 1.0f);

    // If texture alpha < 0.1 discard this fragment.
    if(color.a < 0.1)
        discard;

    fragColor = color;
}
