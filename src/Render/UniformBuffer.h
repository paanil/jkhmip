
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
    void SetUniform(int i, float v);
    void SetUniform(int i, const Vector3 &v);
    void SetUniform(int i, const Matrix4 &v);

    void Bind(uint index);

    void Unbind(uint index);

private:
    uint buffer;
    uint dataSize;
    byte *data;
    std::vector<int> offsets;
};

#endif // __UNIFORMBUFFER_H__
