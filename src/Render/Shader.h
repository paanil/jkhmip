
#ifndef __SHADER_H__
#define __SHADER_H__

#include "../Types.h"

class Matrix4;

class Shader
{
public:
    Shader();
    ~Shader();

    bool Compile(const String &vertSrc, const String &fragSrc);

    void Use();

    void SetProjMatrix(const Matrix4 &proj);
    void SetViewMatrix(const Matrix4 &view);
    void SetModelMatrix(const Matrix4 &model);
    void SetTime(float t);

private:
    uint vert;
    uint frag;
    uint prog;
};

#endif // __SHADER_H__
