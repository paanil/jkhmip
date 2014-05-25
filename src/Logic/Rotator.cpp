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

#include "Rotator.h"
#include "../Scene/Node.h"

void Rotator::SetAxis(const Vector3 &axis)
{
    this->axis = axis;
}

void Rotator::SetAngularVelocity(float degPerSec)
{
    angVel = degPerSec;
}

void Rotator::Update(float dt)
{
    if (node == 0)
        return;

    const Matrix3 &rot = node->GetRotation();
    node->SetRotation(rot * Matrix3::Rotation(axis, angVel * dt));
}
