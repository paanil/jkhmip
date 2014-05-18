
#ifndef __UNIFORMBUFFER_H__
#define __UNIFORMBUFFER_H__

#include "../Types.h"

class UniformBuffer
{
public:
    UniformBuffer();
    ~UniformBuffer();

    void ReserveData(uint dataSize);
    void UpdateData(uint dataSize, const void *data);

    void Bind(uint index);

private:
    uint buffer;
};

#endif // __UNIFORMBUFFER_H__
