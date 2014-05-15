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

#include "Light.h"
#include "../Math/Math.h"

namespace Scene
{

void Light::SetRadius(float radius)
{
    this->radius = radius;
}

float Light::GetRadius() const
{
    return radius;
}

void Light::SetColor(const Vector4 &color)
{
    this->color = color;
}

Vector4 Light::GetColor() const
{
    return color;
}

Vector4 Light::GetLightPos() const
{
    if (radius > 0.0f)
    {
        Vector3 pos = GetPosition(); // TODO: Get world position
        return Vector4(pos.x, pos.y, pos.z, radius);
    }
    Vector3 right, up, look;
    GetBasisVectors(right, up, look);
    return Vector4(up.x, up.y, up.z, radius);
}

bool Light::Affects(const AABB &aabb) const
{
    if (radius > 0.0f) // Point light
    {
        Vector3 pos = GetPosition(); // TODO: Get world position

        pos.x = Math::Clamp(pos.x, aabb.min.x, aabb.max.x) - pos.x;
        pos.y = Math::Clamp(pos.y, aabb.min.y, aabb.max.y) - pos.y;
        pos.z = Math::Clamp(pos.z, aabb.min.z, aabb.max.z) - pos.z;

        return pos.Length() < radius;
    }

    return true; // Directional light affects always
}

void Light::UpdateLightMatrix(const AABB &aabb)
{
    if (radius > 0.0f)
    {
        matrix = Matrix4::Identity();
        return;
    }

    Matrix4 view = Matrix4::Identity();
    for (int i = 0; i < 3; i++)
    {
        view.mat[i][0] = rotation.mat[0][i];
        view.mat[i][1] = rotation.mat[2][i];
        view.mat[i][2] = -rotation.mat[1][i];
    }
    Matrix4 proj = aabb.Transform(view).CreateOrthoProjection();
    matrix = proj * view;
}

const Matrix4 &Light::GetLightMatrix() const
{
    return matrix;
}

void Light::CreateShadowMap(int w, int h)
{
    shadowMap.reset(new Texture());
    shadowMap->CreateTex2D(w, h, TexFmt_DEPTH);
}

Texture *Light::GetShadowMap() const
{
    return shadowMap.get();
}

} // Scene
