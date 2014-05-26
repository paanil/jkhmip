
uniform mat4 ViewProj;
uniform mat4 Model;
uniform mat4 LightMatrix[8];

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec3 position;
out vec2 texcoord;
out vec3 normal;

out vec4 shadowCoord0;
out vec4 shadowCoord1;
out vec4 shadowCoord2;
out vec4 shadowCoord3;
out vec4 shadowCoord4;
out vec4 shadowCoord5;
out vec4 shadowCoord6;
out vec4 shadowCoord7;

void main()
{
    vec4 pos = Model * vec4(Position, 1.0);

    position = pos.xyz;
    texcoord = TexCoord;
    normal = mat3(Model) * Normal;

    vec3 n = normalize(normal);
    shadowCoord0 = LightMatrix[0] * vec4(position + n*0.1, 1.0);
    shadowCoord1 = LightMatrix[1] * vec4(position + n*0.1, 1.0);
    shadowCoord2 = LightMatrix[2] * vec4(position + n*0.1, 1.0);
    shadowCoord3 = LightMatrix[3] * vec4(position + n*0.1, 1.0);
    shadowCoord4 = LightMatrix[4] * vec4(position + n*0.1, 1.0);
    shadowCoord5 = LightMatrix[5] * vec4(position + n*0.1, 1.0);
    shadowCoord6 = LightMatrix[6] * vec4(position + n*0.1, 1.0);
    shadowCoord7 = LightMatrix[7] * vec4(position + n*0.1, 1.0);

    gl_Position = ViewProj * pos;
}
