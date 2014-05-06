
#include "AABB.h"
#include "Math.h"

AABB::AABB() :
    min(0.0f, 0.0f, 0.0f),
    max(0.0f, 0.0f, 0.0f)
{
}

void AABB::Update(const Vector3 &v)
{
    min.x = Math::Min(min.x, v.x);
    min.y = Math::Min(min.y, v.y);
    min.z = Math::Min(min.z, v.z);
    max.x = Math::Max(max.x, v.x);
    max.y = Math::Max(max.y, v.y);
    max.z = Math::Max(max.z, v.z);
}
