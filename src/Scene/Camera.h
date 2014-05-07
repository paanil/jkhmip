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

#ifndef __SCENECAMERA_H__
#define __SCENECAMERA_H__

#include "Node.h"

namespace Scene
{

    /// Camera node.
    ///
    class Camera : public Node
    {
    public:
        /// Initializes identity projection.
        Camera();

        /// Sets orthographic projection.
        void SetOrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar);
        /// Sets perspective projection.
        void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);

        /// Returns the projection matrix.
        Matrix4 GetProjection() const;

    private:
        Matrix4 projection;
    };

} // Scene

#endif // __SCENECAMERA_H__
