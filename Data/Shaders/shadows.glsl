
:include lighting.glsl
:include shadowing.glsl

in vec4 shadowCoord0;
in vec4 shadowCoord1;
in vec4 shadowCoord2;
in vec4 shadowCoord3;
in vec4 shadowCoord4;
in vec4 shadowCoord5;
in vec4 shadowCoord6;
in vec4 shadowCoord7;

const float PI = 3.141592;

vec3 calculateLighting()
{
    vec3 n = normalize(normal);
    vec3 lighting = vec3(0.0);
    lighting += light0.color * lightIntensity(light0, n) * shadowValue(light0, shadowCoord0, ShadowMap0, n);
    lighting += light1.color * lightIntensity(light1, n) * shadowValue(light1, shadowCoord1, ShadowMap1, n);
    lighting += light2.color * lightIntensity(light2, n) * shadowValue(light2, shadowCoord2, ShadowMap2, n);
    lighting += light3.color * lightIntensity(light3, n) * shadowValue(light3, shadowCoord3, ShadowMap3, n);
    lighting += light4.color * lightIntensity(light4, n) * shadowValue(light4, shadowCoord4, ShadowMap4, n);
    lighting += light5.color * lightIntensity(light5, n) * shadowValue(light5, shadowCoord5, ShadowMap5, n);
    lighting += light6.color * lightIntensity(light6, n) * shadowValue(light6, shadowCoord6, ShadowMap6, n);
    lighting += light7.color * lightIntensity(light7, n) * shadowValue(light7, shadowCoord7, ShadowMap7, n);
    return vec3(0.08, 0.08, 0.15) + lighting / PI;
}
