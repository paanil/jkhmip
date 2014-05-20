
:Vert

#version 140

uniform mat4 LightMatrix;
uniform mat4 Model;

in vec3 Position;

void main()
{
    gl_Position = LightMatrix * Model * vec4(Position, 1.0);
}

:Frag

#version 140

out vec4 fragColor;

void main()
{
//    float v = gl_FragCoord.z;
    fragColor = vec4(1.0);
}
