#version 450 core

/* The lighting shader.
 *
 * Alghoritm source (tutorial): https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/lighting.php
 *
 * TODO:
 *  - Flashlight
 *  - Compute normal matrix on CPU and send to uniform. Doing that in the shader wastes a lot of precious GPU cycles.
 *
 * FINISHED:
 *  - Directional light
 *  - Point light
 */

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoord;
layout (location = 3) in vec3 inColor;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoords;
out vec3 fragmentColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // World vertex position.
    fragmentPosition = vec3(model * vec4(inPosition, 1.0));
    // Normal matrix (see TODO):
    //  * http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/
    //  * https://stackoverflow.com/a/21079741
    fragmentNormal = mat3(transpose(inverse(model))) * inNormal;
    // Texture coordinates for fragment shader.
    fragmentTextureCoords = inTextureCoord;
    // Color for fragment shader.
    fragmentColor = inColor;

    // Result = MVP(Projection matrix * View matrix * Model matrix) * vec4(Vertex position, 1.0f)
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}
