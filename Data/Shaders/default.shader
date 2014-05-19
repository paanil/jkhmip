
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

uniform sampler2D DiffuseMap;

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
    vec3  dir;
    float radius;
    float cutoff;
    vec3  color;
    float energy;
    mat4  matrix;
    float noShadows;
};

uniform LightsBlock
{
    LightInfo lights[8];
};

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 fragColor;

vec3 n;

float dirLight(int i)
{
    return dot(n, lights[i].dir);
}

float spotLight(int i)
{
    return 1.0;
}

float pointLight(int i)
{
    vec3 posToLight = lights[i].pos - position;
    vec3 lightDir = normalize(posToLight);
    float dist = length(posToLight);
    float radius = lights[i].radius;
    float dist2 = dist*dist + 0.01;
    float d = dist2 / (radius*radius + 0.01);
    float f = (1.0 - d*d) / (dist2 + 1.0);
    return f * dot(n, lightDir);
}

float lightIntensity(int i)
{
    vec3 light;
    light.r = dirLight(i);
    light.g = spotLight(i);
    light.b = pointLight(i);
    float intensity = dot(lights[i].type, light) * lights[i].energy;
    return max(intensity, 0.0);
}

float fourSamples(float offs, vec4 shadowCoord, sampler2DShadow shadowMap)
{
    offs /= 2048.0;

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

float shadowValue(int i, sampler2DShadow shadowMap)
{
    vec4 shadowCoord = (lights[i].matrix * vec4(position + n*0.1, 1.0));
    return max(fourSamples(0.5, shadowCoord, shadowMap), lights[i].noShadows);
}

vec3 calculateLight(int i, sampler2DShadow shadowMap)
{
    return lights[i].color * lightIntensity(i) * shadowValue(i, shadowMap);
}

vec3 calculateLighting()
{
    vec3 light = vec3(0.1);
    light += calculateLight(0, ShadowMap0);
    light += calculateLight(1, ShadowMap1);
    light += calculateLight(2, ShadowMap2);
    light += calculateLight(3, ShadowMap3);
    light += calculateLight(4, ShadowMap4);
    light += calculateLight(5, ShadowMap5);
    light += calculateLight(6, ShadowMap6);
    light += calculateLight(7, ShadowMap7);
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
    vec3 srgb = 0.662002687 * s1 + 0.684122060 * s2 - 0.323583601 * s3 - 0.225411470 * color;
    return vec4(srgb, 1.0);
//    return vec4(pow(color, vec3(1.0/2.233333)), 1.0);
}

void main()
{
    n = normalize(normal);
    vec3 light = calculateLighting();
    vec3 diffuse = texLinear(DiffuseMap, texcoord);
    fragColor = colorGamma(diffuse * light);
}
