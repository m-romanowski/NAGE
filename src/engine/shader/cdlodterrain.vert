/* Shader based on Filip Strugar paper - CDLOD 2010.
 *
 * Alghoritm source (tutorial): https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/lighting.php
 *
 * TODO:
 *  - Flashlight
 *  - Compute normal matrix on CPU and send to uniform. Doing that in the shader wastes a lot of precious GPU cycles.
 *
 * FINISHED:
 *  - CDLOD
 *  - Directional light
 *  - Point light
 */
#version 450 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoord;
layout (location = 3) in vec4 inColor;

// CDLOD settings
struct CDLOD
{
    vec3 vecOffset;
    float scale;
    float level;
    vec2 gridDimension;
    vec2 morphValue;
};

// MVP matrices
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Current camera position
uniform vec3 cameraPosition;

// LOD
uniform CDLOD cdlod;

// Heightmap
uniform sampler2D heightMapTexture;
uniform vec2 heightMapSize;
uniform float maxHeight;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoords;
out vec4 fragmentColor;

/* Get height value by heightmap texture.
 * height = texture(textureSampler, worldPosition / textureSize).redColor * maxHeight
 *
 * @param _pos - world position (xz)
 * @return height value
 */
float getHeight(vec2 _pos);

/* Calculate texture coordinates.
 * uv = worldPosition / heightmapSize
 *
 * @param _pos - world position
 * @return uv coordinates
 */
vec2 calculateTextureCoords(vec3 _pos);

/* Calculate normal vector.
 *
 * @param _pos - world position
 * @return normal vector (for lighting)
 */
vec3 calculateNormal(vec3 _pos);

/* Calculate morph value (see original Filip Strugar's paper - CDLOD 2010).
 *
 * @param _gridPosition - local position (inPosition)
 * @param _vertex - world position
 * @param _morphValue - morph value = 1.0f - clamp(morphStartValue - eyeDistance * morphEndValue, 0.0f, 1.0f)
 * @return morph value vec2(x, z)
 */
vec2 morphVertex(vec2 _gridPosition, vec2 _vertex, float _morphValue);

void main(void)
{
  	// Base vertex position.
  	vec3 worldPosition = cdlod.vecOffset + cdlod.scale * inPosition;

  	// Distance between current camera position and terrain world position.
    float eyeDist = distance(cameraPosition, worldPosition);
    float morphLerpK  = 1.0f - clamp(cdlod.morphValue.x - eyeDist * cdlod.morphValue.y, 0.0f, 1.0f);

  	// Morph vertex for current world position.
  	worldPosition.xz = morphVertex(inPosition.xz, worldPosition.xz, morphLerpK);
  	worldPosition.y = getHeight(worldPosition.xz);

    // World vertex position.
    fragmentPosition = vec3(model * vec4(worldPosition, 1.0f));
    // Normal matrix (see TODO):
    //  * http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/
    //  * https://stackoverflow.com/a/21079741
    fragmentNormal = mat3(transpose(inverse(model))) * calculateNormal(worldPosition);
    // Texture coordinates for fragment shader.
    fragmentTextureCoords = calculateTextureCoords(worldPosition);
    // Color for fragment shader.
    fragmentColor = inColor;

    gl_Position = projection * view * model * vec4(worldPosition, 1.0);
}

float getHeight(vec2 _pos)
{
    return texture2D(heightMapTexture, _pos / heightMapSize).r * maxHeight;
}

vec2 calculateTextureCoords(vec3 _pos)
{
    return _pos.xz / heightMapSize;
}

vec3 calculateNormal(vec3 pos)
{
    float heightLeft = getHeight(pos.xz + vec2(1, 0));
    float heightRight = getHeight(pos.xz - vec2(1, 0));
    float heightBottom = getHeight(pos.xz + vec2(0, 1));
    float heightTop = getHeight(pos.xz - vec2(0, 1));

    return normalize(cross(vec3(1.0f, heightLeft - heightRight, 0.0f),
        -vec3(0.0f, heightBottom - heightTop, 1.0f)));
}

vec2 morphVertex(vec2 _gridPosition, vec2 _vertex, float _morphValue)
{
	vec2 fracPart = fract(_gridPosition.xy * cdlod.gridDimension.xy * 0.5f) * 2.0f / cdlod.gridDimension.xy;
	return _vertex.xy - fracPart * cdlod.scale * _morphValue;
}
