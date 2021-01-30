// Based on
// 1. http://nishitalab.org/user/nis//cdrom/sig93_nis.pdf
// 2. https://developer.nvidia.com/gpugems/gpugems2/part-ii-shading-lighting-and-shadows/chapter-16-accurate-atmospheric-scattering

#version 450 core

#define PI 3.141592

uniform vec3 cameraPosition;
uniform float g;
uniform int nSamples;
uniform int nLightSamples;
uniform vec3 sunPosition;
uniform float sunIntensity;
uniform float Hr; // Scale height
uniform float Hm;
uniform float Re; // Earth radius
uniform float Ra; // Atmosphere radius
uniform vec3 betaR;
uniform float betaM;

in vec3 fragmentPosition;
out vec4 fragColor;

float rayleighPhase(float cosTheta) {
    float cosTheta2 = cosTheta * cosTheta;
    return 3.0 / (16.0 * PI) * (1.0 + cosTheta2);
}

float miePhase(float cosTheta) {
    float g2 = g * g;
    float cosTheta2 = cosTheta * cosTheta;
    return 3.0 / (8.0 * PI) * ((1.0 - g2) * (cosTheta2 + 1.0)) / (pow(1.0 + g2 - 2.0 * cosTheta * g, 1.5) * (2.0 + g2));
}

vec2 raySphereIntersect(vec3 r0, vec3 rd, float sr) {
    float a = dot(rd, rd);
    float b = 2.0f * dot(rd, r0);
    float c = dot(r0, r0) - (sr * sr);
    float d = (b * b) - 4.0 * a * c;

    if (d < 0.0) {
        return vec2(1e5, -1e5);
    }

    return vec2((-b - sqrt(d)) / (2.0f * a), (-b + sqrt(d)) / (2.0f * a));
}

vec3 scattering(vec3 ray, vec3 origin, vec3 sunPosition) {
    vec3 normalizedRay = normalize(ray);
    vec3 normalizedSunPosition = normalize(sunPosition);

    vec2 t = raySphereIntersect(origin, normalizedRay, Ra);

    if (t.x > t.y) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    t.y = min(t.y, raySphereIntersect(origin, normalizedRay, Re).x);

    // The angle between the light and the view direction.
    float cosTheta = dot(normalizedRay, normalizedSunPosition);
    float rayleighValue = rayleighPhase(cosTheta);
    float mieValue = miePhase(cosTheta);

    float segmentLength = (t.y - t.x) / float(nSamples);

    float tCurrent = 0.0f;
    vec3 sumR = vec3(0.0f, 0.0f, 0.0f);
    vec3 sumM = vec3(0.0f, 0.0f, 0.0f);

    float opticalDepthR = 0.0f;
    float opticalDepthM = 0.0f;

    for (int i = 0; i < nSamples; i++) {
        vec3 samplePosition = origin + normalizedRay * (tCurrent + segmentLength * 0.5);
        float height = length(samplePosition) - Re;

        float hr = exp(-height / Hr) * segmentLength;
        float hm = exp(-height / Hm) * segmentLength;

        opticalDepthR += hr;
        opticalDepthM += hm;

        float segmentLengthLight = raySphereIntersect(samplePosition, normalizedSunPosition, Ra).y / float(nLightSamples);

        float tCurrentLight = 0.0;
        float opticalDepthLightR = 0.0;
        float opticalDepthLightM = 0.0;

        for (int j = 0; j < nLightSamples; j++) {
            vec3 samplePositionLight = samplePosition + normalizedSunPosition * (tCurrentLight + segmentLengthLight * 0.5);
            float heightLight = length(samplePositionLight) - Re;

            opticalDepthLightR += exp(-heightLight / Hr) * segmentLengthLight;
            opticalDepthLightM += exp(-heightLight / Hm) * segmentLengthLight;
            tCurrentLight += segmentLengthLight;
        }

        vec3 attenuation = exp(-(betaR * (opticalDepthR + opticalDepthLightR) + betaM * (opticalDepthM + opticalDepthLightM)));

        sumR += hr * attenuation;
        sumM += hm * attenuation;
        tCurrent += segmentLength;
    }

    vec3 rayleigh = rayleighValue * betaR * sumR;
    vec3 mie = mieValue * betaM * sumM;
    vec3 exposure = 1.0 - exp(-1.0 * (sunIntensity * (rayleigh + mie)));

    return exposure;
}

void main (void) {
    vec3 ray = normalize(fragmentPosition);
    vec3 origin = vec3(0, Re, 0);

    vec3 color = scattering(ray, origin, sunPosition);
    fragColor = vec4(color, 1.0f);
}
