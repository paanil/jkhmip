
:Vert

#version 140

uniform mat4 Proj;
uniform mat4 View;
uniform mat4 Model;

in vec3 Position;

out vec3 position;

void main()
{
    position = mat3(Model) * Position;
    vec3 pos = mat3(View) * Position;
    gl_Position = Proj * vec4(pos, 1.0);
}

:Frag

#version 140

uniform samplerCube Sky;

in vec3 position;

out vec4 fragColor;

void main()
{
    fragColor = texture(Sky, position);
    gl_FragDepth = 1.0;
}
