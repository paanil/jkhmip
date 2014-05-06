
#ifndef __AABB_H__
#define __AABB_H__

#include "Vector3.h"

class AABB
{
public:
    Vector3 min, max;

    AABB();

    void Update(const Vector3 &v);
};

#endif // __AABB_H__
