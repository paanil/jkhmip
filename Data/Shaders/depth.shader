
:Vert

#version 140

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

in vec3 Position;

void main()
{
    vec4 pos_e = View * Model * vec4(Position, 1.0);
    gl_Position = Projection * pos_e;
}

:Frag

#version 140

void main()
{
    gl_FragColor = vec4(1.0);
}
