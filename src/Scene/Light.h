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

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Node.h"
#include "../Render/Texture.h"

#include <memory>

class Frustum;

namespace Scene
{

    class Camera;

    class Light : public Node
    {
        typedef std::unique_ptr<Texture> TexturePtr;

    public:
        Light();

        void SetType(const Vector3 &type);
        void SetRadius(float radius);
        void SetCutoff(float cutoff);
        void SetColor(const Vector3 &color);
        void SetEnergy(float energy);
        void UpdateMatrix(const AABB &visibleScene, const AABB &wholeScene);
        void UpdateMatrixNear(const AABB &visibleScene);
        void CreateShadowMap(int w, int h);

        Vector3 GetType() const;
        Vector3 GetPos();
        Vector3 GetDir();
        float GetRadius() const;
        float GetCutoff() const;
        Vector3 GetColor() const;
        float GetEnergy() const;
        const Matrix4 &GetMatrix() const;
        Texture *GetShadowMap() const;

        bool Affects(const AABB &aabb);

    protected:
        void OnDirty();

    private:
        Vector3     type;
        float       radius;
        float       cutoff;
        Vector3     color;
        float       energy;
        Matrix4     matrix;
        AABB        lightAABB;
        TexturePtr  shadowMap;
    };

    typedef std::vector<Light *> LightList;

} // Scene

#endif // __LIGHT_H__
