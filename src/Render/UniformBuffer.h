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

#ifndef __UNIFORMBUFFER_H__
#define __UNIFORMBUFFER_H__

#include "../Types.h"

#include <vector>

class Vector3;
class Matrix4;

class UniformBuffer
{
public:
    UniformBuffer();
    ~UniformBuffer();

    void ReserveData(uint dataSize);

    void ZeroData();

    void SetUniformOffsets(int count, int *offsets);
    void SetUniform(uint i, float v);
    void SetUniform(uint i, const Vector3 &v);
    void SetUniform(uint i, const Matrix4 &v);

    void Bind(uint index);

    void Unbind(uint index);

private:
    uint buffer;
    uint dataSize;
    byte *data;
    std::vector<int> offsets;
};

#endif // __UNIFORMBUFFER_H__
