
uniform sampler2DShadow ShadowMap0;
uniform sampler2DShadow ShadowMap1;
uniform sampler2DShadow ShadowMap2;
uniform sampler2DShadow ShadowMap3;
uniform sampler2DShadow ShadowMap4;
uniform sampler2DShadow ShadowMap5;
uniform sampler2DShadow ShadowMap6;
uniform sampler2DShadow ShadowMap7;

uniform LightBlock
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

float fourSamples(float offs, vec4 shadowCoord, sampler2DShadow shadowMap)
{
    offs *= shadowCoord.w;

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

float shadowValue(LightInfo light, vec4 shadowCoord, sampler2DShadow shadowMap, vec3 n)
{
    float value = fourSamples(0.5 / light.shadowRes, shadowCoord, shadowMap) * 0.5;
    value += fourSamples(1.5 / light.shadowRes, shadowCoord, shadowMap) * 0.5;
    return max(clamp(value, 0.0, 1.0), light.noShadows);
}
