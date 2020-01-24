/* Materials source: http://devernay.free.fr/cours/opengl/materials.html
 */
#version 450 core

// Define max array size of point lights.
#define MAX_POINT_LIGHTS_COUNT 20

// Material definition.
struct TerrainMaterial
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Point light definition.
struct PointLight
{
    vec3 position;
    vec3 color;
    vec3 attenuation;
};

// Directional light definition.
struct DirectionalLight
{
    vec3 direction;
    vec3 color;
};

// Data from vertex shader.
in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoords;
in vec4 fragmentColor;

// Fragment output color.
out vec4 outFragmentColor;

// Uniforms
uniform TerrainMaterial material; // Material specification.
uniform sampler2D heightMapTexture;

uniform PointLight pointLights[MAX_POINT_LIGHTS_COUNT]; // Array of point lights.
// Current point light count. Fixed size if point light count < MAX_POINT_LIGHTS_COUNT.
// We dont need compute all point lights if some was not defined.
uniform int pointLightCount;

uniform DirectionalLight directionalLight; // Directional light.
uniform vec3 cameraPosition; // Current camera position.

/* Returns result color (ambient + diffuse + specular) for point light.
 *
 * @param { PointLight } _light - point light settings
 * @return { vec3 } - ambient + diffuse + specular color
 */
vec3 getPointLight(PointLight _light);

/* Returns result color (ambient + diffuse + specular) for directional (sun) light.
 *
 * @param { DirectionalLight } - directional light settings
 * @return { vec3 } - ambient + diffuse + specular color
 */
vec3 getDirectionalLight(DirectionalLight _light);

/* Color (rgb) based on textures.
 *
 * @return { vec3 } - rgb color
 */
vec3 combineColorFromTexturesRGB();

/* Color based on textures.
 *
 * @return { vec4 } - rgba color 
 */
vec4 combineColorFromTexturesRGBA();

void main()
{
    // If sent value is incorrect discard fragment.
    if(pointLightCount < 0 || pointLightCount > MAX_POINT_LIGHTS_COUNT)
        discard;
    
    // Compute directional light.
    vec3 dirLight = getDirectionalLight(directionalLight);

    // Compute all point lights that containes specified data.
    vec3 pLights = vec3(0.0f);
    for(int i = 0; i < pointLightCount; i++)
        pLights += getPointLight(pointLights[i]);

    // Fragment output color - sum vec3(ambient + diffuse + specular) of all lights
    outFragmentColor = vec4(dirLight + pLights, 0.8f);
}

vec3 getPointLight(PointLight _light)
{
    // Pre-computing
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(_light.position - fragmentPosition);

    // Ambient
    vec3 ambient = material.ambient * _light.color * combineColorFromTexturesRGB(); // Ambient color = diffuse color.
    
    // Diffuse
    float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = material.diffuse * _light.color * diffuseFactor * combineColorFromTexturesRGB();

    // Specular
    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = material.specular * _light.color * specularFactor;

    /* [Attenuation]
     * We don't want the range of light to be infinite.
     *
     * A = 1.0 / (att.x * dist + att.y * dist + att.z * dist ^ 2)
     * 
     * att: vec3(x, y, z)
     * dist: distance between light position and vertex position.
     */
    float distance = length(_light.position - fragmentPosition);
    float attenuation = 1.0f / (_light.attenuation.x + (_light.attenuation.y * distance)
        + (_light.attenuation.z * distance * distance));

    // And now multiplicate ambient, diffuse and specular values by attenuation.
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 getDirectionalLight(DirectionalLight _light)
{
    // Pre-computing
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(-_light.direction);

    // Ambient
    vec3 ambient = material.ambient * _light.color * combineColorFromTexturesRGB(); // Ambient color = diffuse color.
    
    // Diffuse
    float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = material.diffuse * _light.color * diffuseFactor * combineColorFromTexturesRGB();

    // Specular
    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = material.specular * _light.color * specularFactor;

    return ambient + diffuse + specular;
}

vec3 combineColorFromTexturesRGB()
{
    //return texture2D(material.grass, fragmentTextureCoords).rgb;
    return vec3(0.0f, 0.34f, 0.56f);
}

vec4 combineColorFromTexturesRGBA()
{
    return vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
