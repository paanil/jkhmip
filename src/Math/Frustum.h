
#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "Math.h"

class Frustum
{
public:
    Vector4 planes[6];

    void Construct(float fov, float aspect, float zNear, float zFar)
    {
        fov *= Math::DEG_TO_RAD * 0.5f;
        float si = Math::Sin(fov);
        float co = Math::Cos(fov);

        planes[0] = Vector4(co, 0.0f, si*aspect, 0.0f);
        planes[1] = Vector4(-co, 0.0f, si*aspect, 0.0f);
        planes[2] = Vector4(0.0f, co, si, 0.0f);
        planes[3] = Vector4(0.0f, -co, si, 0.0f);
        planes[4] = Vector4(0.0f, 0.0f, 1.0f, zNear);
        planes[5] = Vector4(0.0f, 0.0f, -1.0f, zFar);
    }

    Frustum Transformed(const Matrix4 &M) const
    {
        Frustum F;
        for (int i = 0; i < 6; i++)
        {
            F.planes[i] = M * Vector4(planes[i].x, planes[i].y, planes[i].z, 0.0f);
            F.planes[i].w = planes[i].w - Vector4(M.m14, M.m24, M.m34, 0.0f).Dot(F.planes[i]);
            F.planes[i].Normalize();
        }
        return F;
    }

    bool TestAABB(const AABB &aabb) const
    {
        for (int i = 0; i < 6; i++)
        {
            if (Math::Max(aabb.min.x * planes[i].x, aabb.max.x * planes[i].x) +
                Math::Max(aabb.min.y * planes[i].y, aabb.max.y * planes[i].y) +
                Math::Max(aabb.min.z * planes[i].z, aabb.max.z * planes[i].z) < -planes[i].w)
                return false;
        }
        return true;
    }
};

#endif // __FRUSTUM_H__
