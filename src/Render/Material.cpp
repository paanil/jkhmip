
#include "Material.h"

Material::Material() :
    shader(0),
    texture(0)
{
}

void Material::SetShader(Shader *shader)
{
    this->shader = shader;
}

Shader *Material::GetShader()
{
    return shader;
}

void Material::SetTexture(Texture *texture)
{
    this->texture = texture;
}

Texture *Material::GetTexture()
{
    return texture;
}
