
:Vert

#version 140

:include shadows_vert.glsl

:Frag

#version 140

uniform sampler2D DiffuseMap;

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 fragColor;

:include shadows.glsl
:include gamma.glsl

void main()
{
    vec3 lighting = calculateLighting();
    vec3 diffuse = texLinear(DiffuseMap, texcoord).rgb;
    fragColor = colorGamma(diffuse * lighting);
}
