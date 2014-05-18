/*
================================================================================

Copyright (c) 2014 Ilari Paananen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

================================================================================
*/

#include "Material.h"

Material::Material() :
    shader(0)
{
    for (int i = 0; i < MAX_MATERIAL_TEXTURES; i++)
        textures[i] = 0;
}

void Material::SetShader(Shader *shader)
{
    this->shader = shader;
}

Shader *Material::GetShader()
{
    return shader;
}

void Material::SetTexture(int i, Texture *texture)
{
    textures[i] = texture;
}

Texture *Material::GetTexture(int i)
{
    return textures[i];
}
