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

#ifndef __MODELCACHE_H__
#define __MODELCACHE_H__

#include "ResourceCache.h"
#include "ObjLoader.h"
#include "../Render/Model.h"

class ModelCache : public ResourceCache<Model>
{
public:
    /// Gets a model identified by the file name.
    Model *Get(const String &file);

private:
    /// Makes unit cube model.
    Model *MakeCube();

private:
    /// Loader for Wavefron .obj files.
    ObjLoader loader;
};

#endif // __MODELCACHE_H__
