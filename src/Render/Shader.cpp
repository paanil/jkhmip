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

#include "Shader.h"
#include "VertexBuffer.h"
#include "../Logger.h"
#include "../Math/Matrix4.h"

#include <GL/glew.h>

Shader::Shader()
{
    vert = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    prog = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(prog);
    glDeleteShader(vert);
    glDeleteShader(frag);
}

bool CompileShader(GLuint shader, const char *source);

bool Shader::Compile(const String &vertSrc, const String &fragSrc)
{
    if (!CompileShader(vert, vertSrc.c_str()) || !CompileShader(frag, fragSrc.c_str()))
        return false;

    for (int i = 0; i < VA_COUNT; i++)
        glBindAttribLocation(prog, i, VA_NAMES[i]);

    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    GLint linked;
    glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE)
    {
        LOG_ERROR("Couldn't link shader.");
        return false;
    }

    Use();
    SetUniform("Diffuse", 0);
    SetUniform("Font", 0);
    SetUniform("ShadowMap0", 1);
    SetUniform("ShadowMap1", 2);
    SetUniform("ShadowMap2", 3);
    SetUniform("ShadowMap3", 4);
    SetUniform("ShadowMap4", 5);
    SetUniform("ShadowMap5", 6);
    SetUniform("ShadowMap6", 7);
    SetUniform("ShadowMap7", 8);

    return true;
}

void Shader::Use()
{
    glUseProgram(prog);
}

void Shader::SetUniform(const String &name, int value)
{
    GLint loc = glGetUniformLocation(prog, name.c_str());
    glUniform1i(loc, value);
}

void Shader::SetUniform(const String &name, float value)
{
    GLint loc = glGetUniformLocation(prog, name.c_str());
    glUniform1f(loc, value);
}

void Shader::SetUniform(const String &name, const Vector3 &value)
{
    GLint loc = glGetUniformLocation(prog, name.c_str());
    glUniform3fv(loc, 1, &value.x);
}

void Shader::SetUniform(const String &name, const Vector4 &value)
{
    GLint loc = glGetUniformLocation(prog, name.c_str());
    glUniform4fv(loc, 1, &value.x);
}

void Shader::SetUniform(const String &name, const Matrix4 &value)
{
    GLint loc = glGetUniformLocation(prog, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, value.data);
}

void Shader::SetUniform(const String &name, int count, const Vector4 *values)
{
    GLint loc = glGetUniformLocation(prog, name.c_str());
    glUniform4fv(loc, count, &values[0].x);
}

void Shader::SetUniform(const String &name, int count, const Matrix4 *values)
{
    GLint loc = glGetUniformLocation(prog, name.c_str());
    glUniformMatrix4fv(loc, count, GL_FALSE, values[0].data);
}

/* Free functions */

GLint GetShaderiv(GLuint shader, GLenum pname)
{
    GLint param = 0;
    glGetShaderiv(shader, pname, &param);
    return param;
}

bool CompileShader(GLuint shader, const char *source)
{
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    if (GetShaderiv(shader, GL_COMPILE_STATUS) == GL_FALSE)
    {
        GLint infoLen = GetShaderiv(shader, GL_INFO_LOG_LENGTH);

        char *info = new char[infoLen + 1];
        glGetShaderInfoLog(shader, infoLen, 0, info);
        info[infoLen] = 0;

        LOG_ERROR("ShaderInfoLog: %", info);
        delete[] info;
        return false;
    }
    return true;
}
