
:Vert

#version 140

uniform mat4 Proj;
uniform vec3 Trans;

in vec3 Position;
in vec2 TexCoord;

out vec2 texcoord;

void main()
{
    texcoord = vec2(TexCoord.x, 1.0 - TexCoord.y);
    gl_Position = Proj * vec4(Position + Trans, 1.0);
}

:Frag

#version 140

uniform sampler2D Font;
uniform vec4 Color;

in vec2 texcoord;

//out vec4 fragColor;

void main()
{
    float r = texture2D(Font, texcoord).r;
    gl_FragColor = vec4(Color.rgb, Color.a * r);
}
