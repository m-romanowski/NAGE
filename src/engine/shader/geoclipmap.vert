/* Shader based on Frank Losasso and Hugues Hoppe paper - http://hhoppe.com/geomclipmap.pdf
 *
 * TODO:
 *  - Compute normal matrix on CPU and send to uniform. Doing that in the shader wastes a lot of precious GPU cycles.
 *  - Flashlight
 *
 * FINISHED:
 *  - Geoclipmaps (wip)
 *  - Directional light
 *  - Point light
 */
#version 450 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoord;
layout (location = 3) in vec4 inColor;

// MVM matrices.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Geoclipmapping settings
struct Geoclipmapping
{
	vec4 scaleFactor;
	float gridSize;
	// fineBlockOrigin.xy: 1 / (w, h) of texture
    // fineBlockOrigin.zw: origin of block in texture
	vec4 fineBlockOrigin;
	sampler2D heightMapTexture;
	vec2 heightMapSize;
	float maxHeight;
	// ((n - 1) / 2) - w - 1
	// n - grid size
	// w - transition width
	vec2 alphaOffset;
	// n / 10
	// n - grid size
	vec2 oneOverWidth;
};

uniform Geoclipmapping gmapping;

// Camera
uniform vec3 cameraPosition;

// Clip planes
uniform vec4 clipPlane;

// Output data to the fragment shader
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


/* Compute coordinates for vertex texture.
 *
 * fineBlockOrigin.xy: 1 / (w, h) of texture
 * fineBlockOrigin.zw: origin of block in texture
 *
 * @return uv coordinates
 */
vec2 calculateTextureCoords();
vec2 calculateTextureCoords(vec3 _pos);

/* Calculate normal vector.
 *
 * @param _pos - world position
 * @return normal vector (for lighting)
 */
vec3 calculateNormal(vec3 _pos);

void main()
{
	// Base vertex position.
  	vec2 xzWorldPosition = gmapping.scaleFactor.zw + (gmapping.scaleFactor.xy * inPosition.xz);

	// Next-coarser level blend
	// Sources:
	// - https://developer.nvidia.com/sites/all/modules/custom/gpugems/books/GPUGems2/elementLinks/ch02_eqn001.jpg
	// - 6.2 http://hhoppe.com/geomclipmap.pdf
	vec2 uv = calculateTextureCoords(vec3(xzWorldPosition.x, 0.0f, xzWorldPosition.y));
	vec4 elevationCoarse = textureLod(gmapping.heightMapTexture, uv, 1.0f);
	float zf = floor(elevationCoarse.x);
	float zc = floor(elevationCoarse.y);
	float zd = zc - zf;

	vec2 alpha = clamp((abs(xzWorldPosition.xy - cameraPosition.xz) - gmapping.alphaOffset) * gmapping.oneOverWidth, 0.0f, 1.0f);
	alpha.x = max(alpha.x, alpha.y);
	float y = zf + (alpha.x * zd);
	y = y * gmapping.scaleFactor.y + getHeight(xzWorldPosition);

	// World vertex position.
    vec3 worldPosition = vec3(xzWorldPosition.x, y, xzWorldPosition.y);

	// World vertex position.
    fragmentPosition = vec3(model * vec4(worldPosition.xyz, 1.0f));
    // Normal matrix (see TODO):
    //  * http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/
    //  * https://stackoverflow.com/a/21079741
    fragmentNormal = mat3(transpose(inverse(model))) * calculateNormal(vec3(0.0f, 0.0f, 0.0f)); // TODO: fix normal calculation.
    // Texture coordinates for fragment shader.
    fragmentTextureCoords = uv;
    // Color for fragment shader.
    fragmentColor = inColor;

    gl_ClipDistance[0] = dot(vec4(worldPosition.xyz, 1.0), clipPlane.xyzw);
    gl_Position = projection * view * model * vec4(worldPosition.xyz, 1.0f);
}

float getHeight(vec2 _pos)
{
    return texture(gmapping.heightMapTexture, _pos / gmapping.heightMapSize).r * gmapping.maxHeight;
}

vec2 calculateTextureCoords(vec3 _pos)
{
	return _pos.xz / gmapping.heightMapSize;
}

vec3 calculateNormal(vec3 _pos)
{
    float heightLeft = getHeight(_pos.xz + vec2(1, 0));
    float heightRight = getHeight(_pos.xz - vec2(1, 0));
    float heightBottom = getHeight(_pos.xz + vec2(0, 1));
    float heightTop = getHeight(_pos.xz - vec2(0, 1));

    return normalize(cross(vec3(1.0f, heightLeft - heightRight, 0.0f),
        -vec3(0.0f, heightBottom - heightTop, 1.0f)));
}
