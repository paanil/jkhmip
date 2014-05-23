
:Vert

#version 140

:include shadows_vert.glsl

:Frag

#version 140

uniform sampler2D TerrainMask;
uniform sampler2D TerrainDiff0;
uniform sampler2D TerrainDiff1;
uniform sampler2D TerrainDiff2;
uniform sampler2D TerrainDiff3;

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 fragColor;

:include shadows.glsl
:include gamma.glsl

vec3 terrainDiffuse()
{
    vec2 uv = position.xz * 0.125;

    vec4 mask = texture(TerrainMask, texcoord);
    mask /= dot(mask, vec4(1.0));

    vec3 diffuse0 = texLinear(TerrainDiff0, uv) * mask.r;
    vec3 diffuse1 = texLinear(TerrainDiff1, uv) * mask.g;
    vec3 diffuse2 = texLinear(TerrainDiff2, uv) * mask.b;
    vec3 diffuse3 = texLinear(TerrainDiff3, uv) * mask.a;

    return diffuse0 + diffuse1 + diffuse2 + diffuse3;
}

void main()
{
    vec3 lighting = calculateLighting();
    vec3 diffuse = terrainDiffuse();
    fragColor = colorGamma(diffuse * lighting);
}
