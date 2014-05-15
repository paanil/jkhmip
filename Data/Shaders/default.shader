
:Vert

#version 140

uniform mat4 Projection;
uniform mat4 View;
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

    gl_Position = Projection * View * pos;
}

:Frag

#version 140

uniform sampler2D Diffuse;

uniform sampler2DShadow ShadowMap0;
uniform sampler2DShadow ShadowMap1;
uniform sampler2DShadow ShadowMap2;
uniform sampler2DShadow ShadowMap3;
uniform sampler2DShadow ShadowMap4;
uniform sampler2DShadow ShadowMap5;
uniform sampler2DShadow ShadowMap6;
uniform sampler2DShadow ShadowMap7;

uniform vec4 LightPosition[8];
uniform vec4 LightColor[8];
uniform mat4 LightMatrix[8];

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 fragColor;

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

float lightIntensity(int i, vec3 n)
{
    vec4 light = LightPosition[i];
    float energy = LightColor[i].a;
    vec3 pos = light.xyz;
    float radius = light.w;
    if (radius > 0.0)
    {
        pos = pos - position;
        float dist = length(pos);
        float dist2 = dist * dist;
        float d = dist2 / (radius * radius);
        float f = max(1.0 - d * d, 0.0) / (dist2 + 1);
        vec3 l = normalize(pos);
        return max(dot(n, l) * f, 0.0) * energy;
    }
    vec3 l = normalize(pos);
    return max(dot(n, l), 0.0) * energy;
}

float shadowValue(int i, vec3 n, sampler2DShadow shadowMap)
{
    vec4 light = LightPosition[i];
    float mx = light.w > 0.0 ? 1.0 : 0.0;

    vec4 shadowCoord = (LightMatrix[i] * vec4(position, 1.0));
//    float bias = 0.0025*tan(acos(max(dot(n, light.xyz), 0.0)));
//    shadowCoord.z -= clamp(bias, 0.0, 0.005);
    shadowCoord.z -= 0.0025;

    float offs = 0.0005;
    float value = textureProj(shadowMap, shadowCoord + vec4(-offs, -offs, 0.0, 0.0));
    value += textureProj(shadowMap, shadowCoord + vec4(offs, -offs, 0.0, 0.0));
    value += textureProj(shadowMap, shadowCoord + vec4(offs, offs, 0.0, 0.0));
    value += textureProj(shadowMap, shadowCoord + vec4(-offs, offs, 0.0, 0.0));

    return max(value / 4.0, mx);
}

vec3 lightningBolt(int i, vec3 n, sampler2DShadow shadowMap)
{
    return LightColor[i].rgb * lightIntensity(i, n) * shadowValue(i, n, shadowMap);
}

void main()
{
    vec3 ambient = vec3(0.1);
    vec3 n = normalize(normal);
    vec3 light = ambient;
    light += lightningBolt(0, n, ShadowMap0);
    light += lightningBolt(1, n, ShadowMap1);
    light += lightningBolt(2, n, ShadowMap2);
    light += lightningBolt(3, n, ShadowMap3);
    light += lightningBolt(4, n, ShadowMap4);
    light += lightningBolt(5, n, ShadowMap5);
    light += lightningBolt(6, n, ShadowMap6);
    light += lightningBolt(7, n, ShadowMap7);
    vec3 diffuse = texLinear(Diffuse, texcoord);
    fragColor = colorGamma(diffuse * light);

//    vec3 n = normalize(normal);
////    gl_FragColor = vec4(n, 1.0);
}
