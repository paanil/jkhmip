
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

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 fragColor;

:include lighting.glsl
:include shadowing.glsl

uniform mat4 LightMatrix[8];

const float PI = 3.141592;

vec3 calculateLighting()
{
    vec3 n = normalize(normal);
    n = mix(-n, n, gl_FrontFacing);

    vec4 shadowCoord0 = LightMatrix[0] * vec4(position + n*0.1, 1.0);
    vec4 shadowCoord1 = LightMatrix[1] * vec4(position + n*0.1, 1.0);
    vec4 shadowCoord2 = LightMatrix[2] * vec4(position + n*0.1, 1.0);
    vec4 shadowCoord3 = LightMatrix[3] * vec4(position + n*0.1, 1.0);
    vec4 shadowCoord4 = LightMatrix[4] * vec4(position + n*0.1, 1.0);
    vec4 shadowCoord5 = LightMatrix[5] * vec4(position + n*0.1, 1.0);
    vec4 shadowCoord6 = LightMatrix[6] * vec4(position + n*0.1, 1.0);
    vec4 shadowCoord7 = LightMatrix[7] * vec4(position + n*0.1, 1.0);

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

:include gamma.glsl

void main()
{
    vec4 color = texLinear(DiffuseMap, texcoord);
    if (color.a < 0.5) discard;
    vec3 diffuse = color.rgb;
    vec3 lighting = calculateLighting();
    fragColor = colorGamma(diffuse * lighting);
}
