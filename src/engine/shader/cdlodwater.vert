/* Shader based on Filip Strugar paper - CDLOD 2010.
 *
 * FINISHED:
 *  - CDLOD
 *  - reflection and refraction map
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
uniform vec2 heightMapSize;
uniform float maxHeight;

// Water settings
uniform float waveNoiseFactor;

// Fragment shader
out vec4 clipSpace;
out vec3 cameraDistance;
out vec2 textureCoords;

/**
 * Calculates morph value (see original Filip Strugar's paper - CDLOD 2010).
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

	  // Distance between current camera position and water world position.
    float eyeDist = distance(cameraPosition, worldPosition);
    float morphLerpK  = 1.0f - clamp(cdlod.morphValue.x - eyeDist * cdlod.morphValue.y, 0.0f, 1.0f);

  	// Morph vertex for current world position.
  	worldPosition.xz = morphVertex(inPosition.xz, worldPosition.xz, morphLerpK);
    clipSpace = projection * view * model * vec4(worldPosition.x, 0.0f, worldPosition.z, 1.0f);

    // Vertex output
    cameraDistance = cameraPosition - worldPosition.xyz;
    textureCoords = (worldPosition.xz / heightMapSize) * waveNoiseFactor;
    gl_Position = clipSpace;
}

vec2 morphVertex(vec2 _gridPosition, vec2 _vertex, float _morphValue)
{
	vec2 fracPart = fract(_gridPosition.xy * cdlod.gridDimension.xy * 0.5f) * 2.0f / cdlod.gridDimension.xy;
	return _vertex.xy - fracPart * cdlod.scale * _morphValue;
}
