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

#ifndef __LOGGING_H__
#define __LOGGING_H__

#include "Format.h"
#include "Types.h"

/// Logger class that can be used like a stream or printf.
///
/// PrintFormatted takes the format string and replaces % -chars
/// with corresponding arguments. % -char after another % -char
/// (i.e. "... %% ...") prints only one % -char and not any arguments.
///
/// EXAMPLES:
///   info.PrintFormatted("Size: %", 10);                       // Size: 10
///   info.PrintFormatted("Couldn't open '%'.", "tiedosto.txt");// Couldn't open 'tiedosto.txt'.
///   info.PrintFormatted("Loading... % %%", 51.7);             // Loading... 51.7 %
///
/// NOTE:   Formatting does not do ANY formatting to the arguments (yet)!
///         Don't put for type specifiers (d for int, s for string, etc.)
///         in the format string and don't put any format params either.
class Logger
{
public:
    Logger();

    void SetStream(std::ostream *stream);
    void SetPrefix(const String &prefix);

    void PrintPrefix();
    void PrintEndLine();

    template <typename T>
    Logger &operator<<(const T &value)
    {
        if (stream)
        {
            *stream << value;
        }
        return *this;
    }

    template <typename... Args>
    void PrintFormatted(const String &fmt, Args... args)
    {
        if (stream)
        {
            PrintPrefix();
            Format(*stream, fmt.c_str(), args...);
            PrintEndLine();
        }
    }

private:
    std::ostream *stream;
    String prefix;

    /* Singleton loggers */
public:
    static Logger &Info();
    static Logger &Debug();
    static Logger &Warning();
    static Logger &Error();

private:
    static Logger info;
    static Logger debug;
    static Logger warning;
    static Logger error;
};

#define LOG_INFO(...)       Logger::Info().PrintFormatted(__VA_ARGS__)
#define LOG_DEBUG(...)      Logger::Debug().PrintFormatted(__VA_ARGS__)
#define LOG_WARNING(...)    Logger::Warning().PrintFormatted(__VA_ARGS__)
#define LOG_ERROR(...)      Logger::Error().PrintFormatted(__VA_ARGS__)

#endif // __LOGGING_H__
