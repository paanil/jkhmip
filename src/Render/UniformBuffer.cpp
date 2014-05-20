
#include "UniformBuffer.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"

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
    glBindBuffer(GL_UNIFORM_BUFFER, buffer);
    glBufferData(GL_UNIFORM_BUFFER, dataSize, 0, GL_DYNAMIC_DRAW);
    if (data) delete[] data;
    data = new byte[dataSize];
    this->dataSize = dataSize;
}

void UniformBuffer::ZeroData()
{
    memset(data, 0, dataSize);
}

void UniformBuffer::SetUniformOffsets(int count, int *offsets)
{
    this->offsets.clear();
    for (int i = 0; i < count; i++)
    {
        this->offsets.push_back(offsets[i]);
    }
}

void UniformBuffer::SetUniform(int i, float v)
{
    memcpy(data + offsets[i], &v, sizeof(float));
}

void UniformBuffer::SetUniform(int i, const Vector3 &v)
{
    memcpy(data + offsets[i], &v.x, sizeof(Vector3));
}

void UniformBuffer::SetUniform(int i, const Matrix4 &v)
{
    memcpy(data + offsets[i], v.data, sizeof(Matrix4));
}

void UniformBuffer::Bind(uint index)
{
    glBindBuffer(GL_UNIFORM_BUFFER, buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, dataSize, data);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, buffer);
}

void UniformBuffer::Unbind(uint index)
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, 0);
}
