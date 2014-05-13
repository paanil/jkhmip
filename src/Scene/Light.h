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

//#include "../Render/Texture.h"

//#include <memory>

namespace Scene
{

    class Light : public Node
    {
//        typedef std::unique_ptr<Texture> TexturePtr;

    public:
        void SetRadius(float radius);
        float GetRadius() const;

        void SetColor(const Vector4 &color);
        Vector4 GetColor() const;

        Vector4 GetLightPos() const;

        bool Affects(const AABB &aabb) const;

//        Texture *GetShadowMap()
//        {
//            return shadowMap.get();
//        }

    private:
        float radius;
        Vector4 color;

//        TexturePtr shadowMap;
    };

    typedef std::vector<Light *> LightList;

} // Scene

#endif // __LIGHT_H__
