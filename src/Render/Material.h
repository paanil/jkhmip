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

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#define MAX_MATERIAL_TEXTURES 8

class Shader;
class Texture;

class Material
{
public:
    Material();

    void SetShader(Shader *shader);
    Shader *GetShader();

    void SetTexture(int i, Texture *texture);
    Texture *GetTexture(int i);

    void SetDoubleSided(bool doubleSided);
    bool IsDoubleSided() const;

private:
    Shader *shader;
    Texture *textures[MAX_MATERIAL_TEXTURES];
    bool doubleSided;
};

#endif // __MATERIAL_H__
