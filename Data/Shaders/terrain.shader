
:Vert

#version 140

uniform mat4 ViewProj;
uniform mat4 Model;

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec3 position;
out vec2 texcoord;
out vec3 normal;

void main()
{
    vec4 pos = Model * vec4(Position, 1.0);

    position = pos.xyz;
    texcoord = TexCoord;
    normal = mat3(Model) * Normal;

    gl_Position = ViewProj * pos;
}

:Frag

#version 140

uniform sampler2D TerrainMask;
uniform sampler2D TerrainDiff0;
uniform sampler2D TerrainDiff1;
uniform sampler2D TerrainDiff2;
uniform sampler2D TerrainDiff3;

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

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 fragColor;

vec3 n;

float dirLight(vec3 L)
{
    return max(dot(n, L), 0.0);
}

float attenuation(float dist, float radius)
{
    float dist2 = dist*dist;
    float d = dist2 / (radius*radius + 0.01);
    return (1.0 - d*d) / (dist2 + 1.0);
}

float spotLight(LightInfo light)
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

    return max(dot(n, L), 0.0) * f * k * 10.0;
}

float pointLight(vec3 pos, float radius)
{
    vec3 L = pos - position;
    float dist = length(L);
    L = normalize(L);
    float f = attenuation(dist, radius);
    return max(dot(n, L), 0.0) * f * 10.0;
}

float lightIntensity(LightInfo light)
{
    vec3 lights;
    lights.r = dirLight(light.dir);
    lights.g = spotLight(light);
    lights.b = pointLight(light.pos, light.radius);
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

float shadowValue(LightInfo light, sampler2DShadow shadowMap)
{
    vec4 shadowCoord = (light.matrix * vec4(position + n*0.1, 1.0));
    float value = fourSamples(0.5 / light.shadowRes, shadowCoord, shadowMap);
    return max(clamp(value, 0.0, 1.0), light.noShadows);
}

vec3 calculateLight(LightInfo light, sampler2DShadow shadowMap)
{
    return light.color * lightIntensity(light) * shadowValue(light, shadowMap);
}

vec3 calculateLighting()
{
    vec3 light = vec3(0.1);
    light += calculateLight(light0, ShadowMap0);
    light += calculateLight(light1, ShadowMap1);
    light += calculateLight(light2, ShadowMap2);
    light += calculateLight(light3, ShadowMap3);
    light += calculateLight(light4, ShadowMap4);
    light += calculateLight(light5, ShadowMap5);
    light += calculateLight(light6, ShadowMap6);
    light += calculateLight(light7, ShadowMap7);
    return light;
}

vec3 texLinear(sampler2D tex, vec2 uv)
{
    vec3 color = texture(tex, uv).rgb;
    return color * (color * (color * 0.305306011 + 0.682171111) + 0.012522878);
}

vec4 colorGamma(vec3 color)
{
    vec3 s1 = sqrt(color);
    vec3 s2 = sqrt(s1);
    vec3 s3 = sqrt(s2);
    color = min(color, vec3(4.0));
    vec3 srgb = 0.662002687 * s1 + 0.684122060 * s2 - 0.323583601 * s3 - 0.225411470 * color;
    return vec4(srgb, 1.0);
}

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
    n = normalize(normal);
    vec3 lighting = calculateLighting();
    vec3 diffuse = terrainDiffuse();
    fragColor = colorGamma(diffuse * lighting);
}
