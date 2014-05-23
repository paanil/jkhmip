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

#include "UniformBuffer.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"
#include "../Logger.h"

#include <cstring>
#include <GL/glew.h>

UniformBuffer::UniformBuffer()
{
    glGenBuffers(1, &buffer);
    data = 0;
    dataSize = 0;
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &buffer);
    if (data) delete[] data;
}

void UniformBuffer::ReserveData(uint dataSize)
{
    if (dataSize)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        glBufferData(GL_UNIFORM_BUFFER, dataSize, 0, GL_DYNAMIC_DRAW);
        if (data) delete[] data;
        data = new byte[dataSize];
        this->dataSize = dataSize;
    }
}

void UniformBuffer::ZeroData()
{
    if (data)
        memset(data, 0, dataSize);
}

void UniformBuffer::SetUniformOffsets(int count, int *offsets)
{
    this->offsets.clear();
    for (int i = 0; i < count; i++)
    {
        uint offset = offsets[i];
        if (offset >= dataSize)
        {
            LOG_WARNING("Invalid uniform offset.");
            offset = 0;
        }
        this->offsets.push_back(offset);
    }
}

void UniformBuffer::SetUniform(uint i, float v)
{
    if (i >= offsets.size() || data == 0) return;
    memcpy(data + offsets[i], &v, sizeof(float));
}

void UniformBuffer::SetUniform(uint i, const Vector3 &v)
{
    if (i >= offsets.size() || data == 0) return;
    memcpy(data + offsets[i], &v.x, sizeof(Vector3));
}

void UniformBuffer::SetUniform(uint i, const Matrix4 &v)
{
    if (i >= offsets.size() || data == 0) return;
    memcpy(data + offsets[i], v.data, sizeof(Matrix4));
}

void UniformBuffer::Bind(uint index)
{
    if (data)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, dataSize, data);
    }
    glBindBufferBase(GL_UNIFORM_BUFFER, index, buffer);
}

void UniformBuffer::Unbind(uint index)
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, 0);
}
