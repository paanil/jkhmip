
:Vert

#version 140

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

in vec3 Position;
in vec2 TexCoord;

out vec2 texcoord;

void main()
{
    texcoord = TexCoord;
    gl_Position = Projection * View * Model * vec4(Position, 1.0);
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
