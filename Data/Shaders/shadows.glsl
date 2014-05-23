
uniform sampler2DShadow ShadowMap0;
uniform sampler2DShadow ShadowMap1;
uniform sampler2DShadow ShadowMap2;
uniform sampler2DShadow ShadowMap3;
uniform sampler2DShadow ShadowMap4;
uniform sampler2DShadow ShadowMap5;
uniform sampler2DShadow ShadowMap6;
uniform sampler2DShadow ShadowMap7;

struct LightInfo
{
    vec3  type;
    vec3  pos;
    float radius;
    vec3  dir;
    float cutoff;
    vec3  color;
    float energy;
    mat4  matrix;
    float shadowRes;
    float noShadows;
};

layout(row_major) uniform LightBlock
{
    LightInfo light0;
    LightInfo light1;
    LightInfo light2;
    LightInfo light3;
    LightInfo light4;
    LightInfo light5;
    LightInfo light6;
    LightInfo light7;
};

float dirLight(vec3 L, vec3 n)
{
    return max(dot(n, L), 0.0);
}

float attenuation(float dist, float radius)
{
    float dist2 = dist*dist;
    float d = dist2 / (radius*radius + 0.01);
    return (1.0 - d*d) / (dist2 + 1.0);
}

float spotLight(LightInfo light, vec3 n)
{
    vec3 L = light.pos - position;
    float dist = length(L);
    L = normalize(L);

    float radius = light.radius;
    float f = attenuation(dist, radius);

    float cosDir = dot(L, light.dir);
    float cosOuter = cos(light.cutoff);
    float cosInner = cos(light.cutoff*0.9f);
    float k = smoothstep(cosOuter, cosInner, cosDir);

    return max(dot(n, L), 0.0) * f * k;
}

float pointLight(vec3 pos, float radius, vec3 n)
{
    vec3 L = pos - position;
    float dist = length(L);
    L = normalize(L);
    float f = attenuation(dist, radius);
    return max(dot(n, L), 0.0) * f;
}

float lightIntensity(LightInfo light, vec3 n)
{
    vec3 lights;
    lights.r = dirLight(light.dir, n);
    lights.g = spotLight(light, n);
    lights.b = pointLight(light.pos, light.radius, n);
    float intensity = dot(light.type, lights) * light.energy;
    return max(intensity, 0.0);
}

float fourSamples(float offs, vec4 shadowCoord, sampler2DShadow shadowMap)
{
    vec4 coord0 = shadowCoord + vec4(-offs, -offs, 0.0, 0.0);
    vec4 coord1 = shadowCoord + vec4( offs, -offs, 0.0, 0.0);
    vec4 coord2 = shadowCoord + vec4( offs,  offs, 0.0, 0.0);
    vec4 coord3 = shadowCoord + vec4(-offs,  offs, 0.0, 0.0);

    vec4 depths;
    depths.r = textureProj(shadowMap, coord0);
    depths.g = textureProj(shadowMap, coord1);
    depths.b = textureProj(shadowMap, coord2);
    depths.a = textureProj(shadowMap, coord3);

    return dot(depths, vec4(0.25));
}

float shadowValue(LightInfo light, sampler2DShadow shadowMap, vec3 n)
{
    vec4 shadowCoord = light.matrix * vec4(position + n*0.1, 1.0);
    float value = fourSamples(0.5 / light.shadowRes, shadowCoord, shadowMap);
    return max(clamp(value, 0.0, 1.0), light.noShadows);
}

vec3 calculateLighting()
{
    vec3 n = normalize(normal);
    vec3 lighting = vec3(0.1);
    lighting += light0.color * lightIntensity(light0, n) * shadowValue(light0, ShadowMap0, n);
    lighting += light1.color * lightIntensity(light1, n) * shadowValue(light1, ShadowMap1, n);
    lighting += light2.color * lightIntensity(light2, n) * shadowValue(light2, ShadowMap2, n);
    lighting += light3.color * lightIntensity(light3, n) * shadowValue(light3, ShadowMap3, n);
    lighting += light4.color * lightIntensity(light4, n) * shadowValue(light4, ShadowMap4, n);
    lighting += light5.color * lightIntensity(light5, n) * shadowValue(light5, ShadowMap5, n);
    lighting += light6.color * lightIntensity(light6, n) * shadowValue(light6, ShadowMap6, n);
    lighting += light7.color * lightIntensity(light7, n) * shadowValue(light7, ShadowMap7, n);
    return lighting;
}
