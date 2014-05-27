
struct LightInfo
{
    vec3  type;
    vec3  pos;
    float radius;
    vec3  dir;
    float cutoff;
    vec3  color;
    float energy;
    float shadowRes;
    float noShadows;
};

float dirLight(vec3 L, vec3 n)
{
    return max(dot(n, L), 0.0);
}

float attenuation(float dist, float radius)
{
    float dist2 = dist*dist;
    float d = dist2 / (radius*radius + 0.01);
    return (1.0 - d*d) / (dist2 + 1.0);
}

float spotLight(LightInfo light, vec3 n)
{
    vec3 L = light.pos - position;
    float dist = length(L);
    L = normalize(L);

    float radius = light.radius;
    float f = attenuation(dist, radius);

    float cosDir = dot(L, light.dir);
    float cosOuter = cos(light.cutoff);
    float cosInner = cos(light.cutoff*0.9f);
    float k = smoothstep(cosOuter, cosInner, cosDir);

    return max(dot(n, L), 0.0) * f * k;
}

float pointLight(vec3 pos, float radius, vec3 n)
{
    vec3 L = pos - position;
    float dist = length(L);
    L = normalize(L);
    float f = attenuation(dist, radius);
    return max(dot(n, L), 0.0) * f;
}

float lightIntensity(LightInfo light, vec3 n)
{
    vec3 lights;
    lights.r = dirLight(light.dir, n);
    lights.g = spotLight(light, n);
    lights.b = pointLight(light.pos, light.radius, n);
    float intensity = dot(light.type, lights) * light.energy;
    return max(intensity, 0.0);
}
