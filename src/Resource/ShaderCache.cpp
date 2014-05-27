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

#include "ShaderCache.h"
#include "../Logger.h"
#include "../Str.h"

#include <fstream>

Shader *ShaderCache::Load(const String &filePath)
{
    static const String debugVertSrc =
        "#version 140\n"
        "uniform mat4 ViewProj;"
        "uniform mat4 Model;"
        "in vec3 Position;"
        "void main() {"
        "gl_Position = ViewProj * Model * vec4(Position, 1.0);"
        "}";

    static const String debugFragSrc =
        "#version 140\n"
        "void main() {"
        "gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);"
        "}";

    Shader *shader = new Shader();

    String vertSrc, fragSrc;
    if (!LoadSourceFile(filePath, vertSrc, fragSrc) ||
        !shader->Compile(vertSrc, fragSrc))
    {
        LOG_INFO("Using debug shader.");

        if (!shader->Compile(debugVertSrc, debugFragSrc))
        {
            delete shader;
            return 0;
        }
    }

    return shader;
}

bool ReadLines(const String &file, String &vertSrc, String &fragSrc, String *dst, const String &dir)
{
    std::ifstream f(file.c_str());
    if (!f.is_open()) return false;

    String line;
    while (std::getline(f, line))
    {
        if (!line.empty())
        {
            if (line[0] == ':')
            {
                String first, second;
                size_t pos = line.find_first_of(' ');
                if (pos == String::npos)
                    first = line;
                else
                {
                    first = line.substr(0, pos);
                    second = line.substr(pos+1);
                }

                if (StrIEquals(first, ":vert"))
                    dst = &vertSrc;
                else if (StrIEquals(first, ":frag"))
                    dst = &fragSrc;
                else if (first == ":include")
                {
                    if (dst == 0)
                    {
                        LOG_ERROR("Include before selecting vert or frag.");
                        return false;
                    }
                    if (!ReadLines(dir + second, vertSrc, fragSrc, dst, dir))
                    {
                        LOG_ERROR("Couldn't include file '%'.", second);
                        return false;
                    }
                }
                else
                {
                    LOG_ERROR("Invalid line starting with ':'.");
                    return false;
                }
            }
            else if (dst)
            {
                dst->append(line);
                dst->push_back('\n');
            }
        }
    }

    f.close();
    return true;
}

bool ShaderCache::LoadSourceFile(const String &file, String &vertSrc, String &fragSrc)
{
    LOG_INFO("Loading shader '%'...", file);

    if (!ReadLines(file, vertSrc, fragSrc, 0, GetDirectory()))
    {
        LOG_ERROR("Couldn't open file.");
        return false;
    }

    return true;
}
