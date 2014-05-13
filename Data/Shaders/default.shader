
:Vert

#version 140

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;

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

uniform vec4 LightPosition[8];
uniform vec4 LightColor[8];
//uniform vec3 LightAmbient;

in vec3 position;
in vec2 texcoord;
in vec3 normal;

vec3 texLinear(sampler2D tex, vec2 uv)
{
    vec3 e = vec3(2.2);
    vec3 color = texture2D(tex, uv).rgb;
    return pow(color, e);
}

vec4 colorGamma(vec3 color)
{
    vec3 e = vec3(1.0/2.2);
    return vec4(pow(color, e), 1.0);
}

float lightIntensity(vec4 lightPos, vec3 n)
{
    vec3 light = lightPos.xyz;
    float radius = lightPos.w;
    if (radius > 0.0)
    {
        light = light - position;
        float dist = length(light);
        float dist2 = dist * dist;
        float d = dist2 / (radius * radius);
        float f = max(1.0 - d * d, 0.0) / (dist2 + 1);
        light = normalize(light);
        return max(dot(n, light) * f, 0.0);
    }
    light = normalize(light);
    return max(dot(n, light), 0.0);
}

void main()
{
    vec3 LightAmbient = vec3(0.01);
    vec3 n = normalize(normal);
    vec3 light = LightAmbient;
    light += LightColor[0].rgb * LightColor[0].a * lightIntensity(LightPosition[0], n);
    light += LightColor[1].rgb * LightColor[1].a * lightIntensity(LightPosition[1], n);
    light += LightColor[2].rgb * LightColor[2].a * lightIntensity(LightPosition[2], n);
    light += LightColor[3].rgb * LightColor[3].a * lightIntensity(LightPosition[3], n);
    light += LightColor[4].rgb * LightColor[4].a * lightIntensity(LightPosition[4], n);
    light += LightColor[5].rgb * LightColor[5].a * lightIntensity(LightPosition[5], n);
    light += LightColor[6].rgb * LightColor[6].a * lightIntensity(LightPosition[6], n);
    light += LightColor[7].rgb * LightColor[7].a * lightIntensity(LightPosition[7], n);
    vec3 diffuse = texLinear(Diffuse, texcoord);
    gl_FragColor = colorGamma(diffuse * light);

//    vec3 n = normalize(normal);
////    gl_FragColor = vec4(n, 1.0);
}
