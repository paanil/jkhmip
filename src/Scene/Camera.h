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

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Node.h"
#include "../Math/Frustum.h"

namespace Scene
{

    /// Camera node.
    ///
    class Camera : public Node
    {
    public:
        Camera();

        void SetParameters(float fov, float zNear, float zFar);
        void SetAspectRatio(float aspect);

        /// Returns the projection matrix.
        const Matrix4 &GetProjection() const;

    private:
        void UpdateProjection();

    private:
        float fov;
        float aspect;
        float zNear;
        float zFar;

        Matrix4 projection;
    };

} // Scene

#endif // __CAMERA_H__
