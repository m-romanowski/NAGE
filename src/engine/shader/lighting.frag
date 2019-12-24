#version 450 core

// Materials source: http://devernay.free.fr/cours/opengl/materials.html

// Define max array size of point lights.
#define MAX_POINT_LIGHTS_COUNT 20

// Material definition.
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    sampler2D diffuseTexture;
    sampler2D specularTexture;
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
in vec3 vertexColor;

// Fragment output color.
out vec4 outFragmentColor;

// Uniforms
uniform Material material; // Material specification.

uniform PointLight pointLights[MAX_POINT_LIGHTS_COUNT]; // Array of point lights.
// Current point light count. Fixed size if point light count < MAX_POINT_LIGHTS_COUNT.
// We dont need compute all point lights if some was not defined.
uniform int pointLightCount;

uniform DirectionalLight directionalLight; // Directional light.
uniform vec3 cameraPosition; // Current camera position.

vec3 getPointLight(PointLight _light);
vec3 getDirectionalLight(DirectionalLight _light);

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
    outFragmentColor = vec4(dirLight + pLights, 1.0f);
}

vec3 getPointLight(PointLight _light)
{
    // Pre-computing
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(_light.position - fragmentPosition);

    // Ambient
    vec3 ambient = material.ambient * _light.color
        * texture(material.diffuseTexture, fragmentTextureCoords).rgb; // Ambient color = diffuse color.
    
    // Diffuse
    float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = material.diffuse * _light.color * diffuseFactor * texture(material.diffuseTexture,
        fragmentTextureCoords).rgb;

    // Specular
    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = material.specular * _light.color * specularFactor * texture(material.specularTexture,
        fragmentTextureCoords).rgb;

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
    vec3 ambient = material.ambient * _light.color
        * texture(material.diffuseTexture, fragmentTextureCoords).rgb; // Ambient color = diffuse color.
    
    // Diffuse
    float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = material.diffuse * _light.color * diffuseFactor * texture(material.diffuseTexture,
        fragmentTextureCoords).rgb;

    // Specular
    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = material.specular * _light.color * specularFactor * texture(material.specularTexture,
        fragmentTextureCoords).rgb;

    return ambient + diffuse + specular;
}
