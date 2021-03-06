
:Vert

#version 140

uniform mat4 LightMatrix;
uniform mat4 Model;

in vec3 Position;
in vec2 Texcoord;

out vec2 texcoord;

void main()
{
    texcoord = Texcoord;

    gl_Position = LightMatrix * Model * vec4(Position, 1.0);
}

:Frag

#version 140

uniform sampler2D Mask;

in vec2 texcoord;

out vec4 fragColor;

void main()
{
    vec4 color = texture(Mask, texcoord);
    if (color.a < 0.5) discard;
//    float v = gl_FragCoord.z;
    fragColor = vec4(1.0);
}
