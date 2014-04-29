
:Vert

#version 140

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec2 texcoord;
out vec3 normal;
out vec3 light;

void main()
{
    mat3 NormalMatrix = mat3(Model);

    texcoord = TexCoord;
    normal = NormalMatrix * Normal;
    float ang = Time * 0.25;
    light = vec3(cos(ang), sin(ang), 0.0);

    gl_Position = Projection * View * Model * vec4(Position, 1.0);
}

:Frag

#version 140

uniform sampler2D Diffuse;

in vec2 texcoord;
in vec3 normal;
in vec3 light;

//out vec4 fragColor;

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

void main()
{
    vec3 n = normalize(normal);
//    gl_FragColor = vec4(n, 1.0);
    vec3 l = normalize(light);
    float ndotl = max(dot(n, l), 0.0);
    vec3 up = vec3(0.0, 1.0, 0.0);
    float f = smoothstep(-0.2, 0.2, dot(l, up));
    float ambf = max(dot(n, up), 0.0) * 0.95 + 0.05;
    vec3 ambient1 = vec3(0.01, 0.01, 0.05);
    vec3 ambient2 = vec3(0.03, 0.03, 0.03);
    vec3 suncolor = vec3(1.0, 0.8, 0.5);
    vec3 diffuse = texLinear(Diffuse, texcoord);
    gl_FragColor = colorGamma(diffuse * mix(ambient1 * ambf, ambient2 + suncolor * ndotl, f));
}
