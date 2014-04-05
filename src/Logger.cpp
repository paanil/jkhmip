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

#include "Logger.h"

/* The static logger instances */

Logger Logger::info;
Logger Logger::debug;
Logger Logger::warning;
Logger Logger::error;

/* Logger functions */

Logger::Logger() :
    stream(0),
    prefix()
{
}

void Logger::SetStream(std::ostream *stream)
{
    this->stream = stream;
}

void Logger::SetPrefix(const String &prefix)
{
    this->prefix = prefix;
}

void Logger::PrintPrefix()
{
    *this << prefix;
}

void Logger::PrintEndLine()
{
    if (stream)
    {
        *stream << std::endl;
    }
}

/* Static getters */

Logger &Logger::Info()
{
    return info;
}

Logger &Logger::Debug()
{
    return debug;
}

Logger &Logger::Warning()
{
    return warning;
}

Logger &Logger::Error()
{
    return error;
}
