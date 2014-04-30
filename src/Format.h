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

#ifndef __FORMAT_H__
#define __FORMAT_H__

#include <ostream>
#include <string>
#include <sstream>

inline void Format(std::ostream &out, const char *fmt)
{
    for (const char *c = fmt; *c; c++)
    {
        if (*c == '%')
        {
            if (*(c + 1) == '%')
                c++;    // % -char escaped with % (something like "... 100%% ...")
            else
                c++;    // % -char but no more args nor escape for another % -char!!! Skip it.
                        //TODO: warning/error/assert
        }

        out << *c;
    }
}

template <class T, class... Args>
void Format(std::ostream &out, const char *fmt, const T &value, Args... args)
{
    for (const char *c = fmt; *c; ++c)
    {
        if (*c == '%')
        {
            c++;
            if (*c != '%')
            {
                out << value;
                Format(out, c, args...);
                return;
            }
        }

        out << *c;
    }

    // There are more args than % -chars!!!
    //TODO: warning/error/assert
}

template <class... Args>
void Format(std::string &str, const char *fmt, Args... args)
{
    std::ostringstream out;
    Format(out, fmt, args...);

    str = out.str();
}

#endif // __FORMAT_H__
