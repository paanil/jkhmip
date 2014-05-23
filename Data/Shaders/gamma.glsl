
vec3 texLinear(sampler2D tex, vec2 uv)
{
    vec3 color = texture(tex, uv).rgb;
    return color * (color * (color * 0.305306011 + 0.682171111) + 0.012522878);
}

vec4 colorGamma(vec3 color)
{
    vec3 s1 = sqrt(color);
    vec3 s2 = sqrt(s1);
    vec3 s3 = sqrt(s2);
    color = min(color, vec3(4.0));
    vec3 srgb = 0.662002687 * s1 + 0.684122060 * s2 - 0.323583601 * s3 - 0.225411470 * color;
    return vec4(srgb, 1.0);
}
