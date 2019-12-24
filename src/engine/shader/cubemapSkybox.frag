#version 450 core

uniform samplerCube skybox;

in vec3 textureCoords;
out vec4 fragColor;

void main()
{    
    fragColor = texture(skybox, textureCoords);
}
