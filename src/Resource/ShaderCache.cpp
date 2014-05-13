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
        "uniform mat4 Projection;"
        "uniform mat4 View;"
        "uniform mat4 Model;"
        "in vec3 Position;"
        "void main() {"
        "gl_Position = Projection * View * Model * vec4(Position, 1.0);"
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

bool ShaderCache::LoadSourceFile(const String &file, String &vertSrc, String &fragSrc)
{
    LOG_INFO("Loading shader '%'...", file);

    std::ifstream f(file.c_str());

    if (!f.is_open())
    {
        LOG_ERROR("Couldn't open file.");
        return false;
    }

    int dst = 0;
    String line;

    while (std::getline(f, line))
    {
        if (!line.empty())
        {
            if (StrIEquals(line, ":vert"))
            {
                if (dst & 1)
                {
                    LOG_ERROR("Multiple vertex shaders in one file.");
                    return false;
                }
                dst = (dst & 3) | 0x11;
            }
            else if (StrIEquals(line, ":frag"))
            {
                if (dst & 2)
                {
                    LOG_ERROR("Multiple fragment shaders in one file.");
                    return false;
                }
                dst = (dst & 3) | 0x22;
            }
            else
            {
                if (dst & 0x10)
                    vertSrc.append(line);
                else if (dst & 0x20)
                    fragSrc.append(line);
            }
        }
        if (!(dst & 1) || (dst & 0x10))
            vertSrc.push_back('\n');
        if (!(dst & 2) || (dst & 0x20))
            fragSrc.push_back('\n');
    }

    return true;
}
