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
#include "../Logger.h"



namespace Scene
{



Light::Light() :
    type(1.0f, 0.0f, 0.0f),
    radius(5.0f),
    cutoff(Math::PI/2.0f),
    color(1.0f, 1.0f, 1.0f),
    energy(1.0f),
    matrix(),
    shadowMap(),
    lightAABB()
{
}



void Light::SetType(const Vector3 &type)
{
    this->type = type;
}

void Light::SetRadius(float radius)
{
    this->radius = radius;
}

void Light::SetCutoff(float cutoff)
{
    this->cutoff = cutoff;
}

void Light::SetColor(const Vector3 &color)
{
    this->color = color;
}

void Light::SetEnergy(float energy)
{
    this->energy = energy;
}

void Light::UpdateMatrix(const AABB &visibleScene, const AABB &wholeScene)
{
    if (type.x > 0.0f)
    {
        Matrix4 view = GetInverseWorldTransform();
        lightAABB = visibleScene.Transform(view);
        lightAABB.min.z = wholeScene.Transform(view).min.z;
        Matrix4 proj = lightAABB.CreateOrthoProjection();
        matrix = proj * view;
    }
    else if (type.y > 0.0f)
    {
        Matrix4 view = GetInverseWorldTransform();
        Matrix4 proj = Matrix4::Perspective(2.0f * cutoff * Math::RAD_TO_DEG, 1.0f, radius * 0.001f, radius);
        matrix = proj * view;
    }
}

void Light::UpdateMatrixNear(const AABB &visibleScene)
{
    if (type.x > 0.0f)
    {
        Matrix4 view = GetInverseWorldTransform();
//        lightAABB.min.z = visibleScene.Transform(view).min.z;
        lightAABB = visibleScene.Transform(view);
        Matrix4 proj = lightAABB.CreateOrthoProjection();
        matrix = proj * view;
    }
//    else if (type.y > 0.0f)
//    {
//        Matrix4 view = GetInverseWorldTransform();
//        float min_z = visibleScene.Transform(view).min.z;
//        float zNear = Math::Max(radius * 0.001f, min_z - radius * 0.001f);
//        LOG_DEBUG("min_z: % zNear: %", min_z, zNear);
//        Matrix4 proj = Matrix4::Perspective(2.0f * cutoff * Math::RAD_TO_DEG, 1.0f, zNear, radius);
//        matrix = proj * view;
//    }
}

void Light::CreateShadowMap(int shadowRes)
{
    shadowMap.reset(new Texture());
    shadowMap->CreateTex2D(shadowRes, shadowRes, TexFmt_DEPTH);
    this->shadowRes = shadowRes;
}



Vector3 Light::GetType() const
{
    return type;
}

Vector3 Light::GetPos()
{
    const Matrix4 &m = GetWorldTransform();
    return Vector3(m.m14, m.m24, m.m34);
}

Vector3 Light::GetDir()
{
    const Matrix4 &m = GetWorldTransform();
    return Vector3(-m.m13, -m.m23, -m.m33);
}

float Light::GetRadius() const
{
    return radius;
}

float Light::GetCutoff() const
{
    return cutoff;
}

Vector3 Light::GetColor() const
{
    return color;
}

float Light::GetEnergy() const
{
    return energy;
}

const Matrix4 &Light::GetMatrix() const
{
    return matrix;
}

int Light::GetShadowRes() const
{
    return shadowRes;
}

Texture *Light::GetShadowMap() const
{
    return shadowMap.get();
}

const AABB &Light::GetLightAABB()
{
    if (type.y > 0.0f)
    {
        const Matrix4 &m = GetWorldTransform();

        Vector3 r(m.m11, m.m21, m.m31);
        Vector3 u(m.m12, m.m22, m.m32);
        Vector3 l(m.m13, m.m23, m.m33);
        Vector3 p(m.m14, m.m24, m.m34);

        Vector3 center = p + l * radius;

        float s = Math::Tan(cutoff) * radius;

        lightAABB = AABB::Degenerate();
        lightAABB.Update(p);
        lightAABB.Update(center - r*s - u*s);
        lightAABB.Update(center + r*s - u*s);
        lightAABB.Update(center - r*s + u*s);
        lightAABB.Update(center + r*s + u*s);
    }
    return lightAABB;
}



bool Light::Affects(const AABB &aabb)
{
    if (type.x > 0.0f) // Directional light
        return true;

    if (type.y > 0.0f) // Spot light
    {
        UpdateMatrix(AABB(), AABB());
        Frustum frus = Frustum::Extract(matrix);
        return frus.TestAABB(aabb);
    }

    // Point light
    const Matrix4 &m = GetWorldTransform();
    Vector3 pos = Vector3(m.m14, m.m24, m.m34);

    pos.x = Math::Clamp(pos.x, aabb.min.x, aabb.max.x) - pos.x;
    pos.y = Math::Clamp(pos.y, aabb.min.y, aabb.max.y) - pos.y;
    pos.z = Math::Clamp(pos.z, aabb.min.z, aabb.max.z) - pos.z;

    return pos.Length() < radius;
}



void Light::OnDirty()
{
    if (type.x > 0.0f)
    {
        // We don't want any translation for a directional light.
        position = Vector3(0.0f, 0.0f, 0.0f);
    }
}



} // Scene
