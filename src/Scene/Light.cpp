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
#include "Camera.h"
#include "../Math/Frustum.h"
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

Vector4 Light::GetLightPos()
{
    const Matrix4 &m = GetWorldTransform();
    if (radius > 0.0f)
        return Vector4(m.m14, m.m24, m.m34, radius);
    return Vector4(-m.m13, -m.m23, -m.m33, radius);
}

bool Light::Affects(const AABB &aabb)
{
    if (radius > 0.0f) // Point light
    {
        const Matrix4 &m = GetWorldTransform();
        Vector3 pos = Vector3(m.m14, m.m24, m.m34);

        pos.x = Math::Clamp(pos.x, aabb.min.x, aabb.max.x) - pos.x;
        pos.y = Math::Clamp(pos.y, aabb.min.y, aabb.max.y) - pos.y;
        pos.z = Math::Clamp(pos.z, aabb.min.z, aabb.max.z) - pos.z;

        return pos.Length() < radius;
    }

    return true; // Directional light affects always
}

void Light::UpdateLightMatrix(const AABB &visibleScene, const AABB &wholeScene)
{
    if (radius > 0.0f)
    {
        matrix = Matrix4::Identity();
        return;
    }

    Matrix4 view = GetInverseWorldTransform();
    lightAABB = visibleScene.Transform(view);
    lightAABB.min.z = wholeScene.Transform(view).min.z;
    Matrix4 proj = lightAABB.CreateOrthoProjection();
    matrix = proj * view;
}

void Light::UpdateLightMatrixNear(const AABB &visibleScene)
{
    Matrix4 view = GetInverseWorldTransform();
    lightAABB.min.z = visibleScene.Transform(view).min.z;
    Matrix4 proj = lightAABB.CreateOrthoProjection();
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

void Light::OnDirty()
{
    if (radius <= 0.0f)
    {
        SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    }
}

} // Scene
