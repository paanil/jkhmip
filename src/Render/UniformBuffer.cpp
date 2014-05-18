
#include "UniformBuffer.h"

#include <GL/glew.h>

UniformBuffer::UniformBuffer()
{
    glGenBuffers(1, &buffer);
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &buffer);
}

void UniformBuffer::ReserveData(uint dataSize)
{
    glBindBuffer(GL_UNIFORM_BUFFER, buffer);
    glBufferData(GL_UNIFORM_BUFFER, dataSize, 0, GL_DYNAMIC_DRAW);
}

void UniformBuffer::UpdateData(uint dataSize, const void *data)
{
    glBindBuffer(GL_UNIFORM_BUFFER, buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, dataSize, data);
}

void UniformBuffer::Bind(uint index)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, index, buffer);
}
