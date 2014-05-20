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

#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
#include <cstdint>

/// Hide the use of std::string so later can be
/// replaced with own string implementation that is
/// compatible with std::string.
typedef std::string String;

typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef uint8_t  byte;
typedef uint32_t uint;

#endif // __TYPES_H__
