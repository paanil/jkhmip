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

#include "Str.h"

#include <cctype>

bool StrIEquals(const String &str1, const String &str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }

    const char *s1 = str1.c_str();
    const char *s2 = str2.c_str();

    for (; *s1 && *s2; s1++, s2++)
    {
        if (tolower(*s1) != tolower(*s2))
        {
            return false;
        }
    }
    return true;
}
