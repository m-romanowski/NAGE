#version 450 core

// Vertex shader output.
in vec4 clipSpace;
in vec3 cameraDistance;
in vec2 textureCoords;

// Fragment output color.
out vec4 outFragmentColor;

// Uniforms
uniform sampler2D reflectionTexture; // Water reflection effect.
uniform sampler2D refractionTexture; // Water refraction effect.
uniform sampler2D flowMapTexture; // Flow map effect.
uniform float waveFrequency;
uniform float waveMoveOffset;

void main()
{
    // Calculate flow map noise factor.
    vec2 flowNoiseFactor = (texture(flowMapTexture, vec2(textureCoords.x + waveMoveOffset, textureCoords.y)).rg - 0.5f * 2.0f) * waveFrequency;
    flowNoiseFactor += (texture(flowMapTexture, vec2(-textureCoords.x, textureCoords.y + waveMoveOffset)).rg - 0.5f * 2.0f) * waveFrequency;

    // Calculate reflaction and refraction factor.
    vec2 normalizedCoords = ((clipSpace.xy / clipSpace.w) * 0.5f) + vec2(0.5f);
    vec2 reflectionTextureCoords = vec2(normalizedCoords.x, -normalizedCoords.y) + flowNoiseFactor;
    vec2 refractionTextureCoords = vec2(normalizedCoords.x, normalizedCoords.y) + flowNoiseFactor;

    // We need to clamp result relfection and refraction texture coordinates
    // (sometimes flow noise factor going below zero) and we have visual bug on the egdes of the screen.
    // We can fix that clamping texture coords to [0.01, 0.99] range values.
    reflectionTextureCoords.x = clamp(reflectionTextureCoords.x, 0.01, 0.99);
    reflectionTextureCoords.y = clamp(reflectionTextureCoords.y, -0.99, -0.01);
    refractionTextureCoords = clamp(refractionTextureCoords, 0.01, 0.99);    

    vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoords.xy);
    vec4 refractionColor = texture(refractionTexture, refractionTextureCoords.xy);

    // Set fresnel effect.
    vec3 normalizedCameraDistance = normalize(cameraDistance);
    float fresnelEffectValue = dot(normalizedCameraDistance, vec3(0.0f, 1.0f, 0.0f));

    outFragmentColor = mix(vec4(reflectionColor.xyz, 1.0f), vec4(refractionColor.xyz, 1.0f), fresnelEffectValue);
}
