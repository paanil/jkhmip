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

#ifndef __SHADER_H__
#define __SHADER_H__

#include "../Types.h"

class Matrix4;
class Vector4;
class Vector3;

/// Shader class.
///
class Shader
{
public:
    /// Gets gl ids for vertex and fragment shaders and for the program.
    Shader();
    /// Releases gl vertex and fragment shaders and the program.
    ~Shader();

    /// Compiles vertex and fragment shaders with given sources and links the program.
    /// Returns false on fail.
    bool Compile(const String &vertSrc, const String &fragSrc);

    /// Uses the shader program.
    void Use();

    void SetUniform(const String &name, int value);
    void SetUniform(const String &name, float value);
    void SetUniform(const String &name, const Vector3 &value);
    void SetUniform(const String &name, const Vector4 &value);
    void SetUniform(const String &name, const Matrix4 &value);
    void SetUniform(const String &name, int count, const Vector4 *values);
    void SetUniform(const String &name, int count, const Matrix4 *values);

    int GetUniformBlockSize(const char *name);
    void GetUniformOffsets(const int count, const char **names, int *offsets);

private:
    /// GL ids.
    uint vert;
    uint frag;
    uint prog;
};

#endif // __SHADER_H__
