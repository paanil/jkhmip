
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
