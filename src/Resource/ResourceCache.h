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

#ifndef __RESOURCECACHE_H__
#define __RESOURCECACHE_H__

#include "../Types.h"

#include <memory>
#include <map>

/// Templated class that specific resource cahces are derived from.
/// It caches resources so they won't be loaded every time they are needed.
/// If same resource is needed frequently, the pointer should be kept for efficiency.
/// Note that the cache owns the resource. Don't try to delete it.
/// The derived resource cache should implement the Load -method.
template <class T>
class ResourceCache
{
    /// Useful typedefs.
    typedef std::unique_ptr<T> ResourcePtr;
    typedef std::map<String, ResourcePtr> ResourceMap;

public:
    /// Virtual destructor
    virtual ~ResourceCache()
    {
    }

    /// Sets the 'direcotry' where the resources are expected
    /// to be found. The string needs to end with '/' -char.
    void SetDirectory(const String &dir)
    {
        direcotry = dir;
    }

    /// Gets a resource identified by the file name.
    /// The resource is loaded if it's not in the cache.
    /// The file name is expected to be relative to the 'direcotry'.
    T *Get(const String &file)
    {
        auto it = resources.find(file);
        if (it != resources.end())
        {
            return it->second.get();
        }

        T *resource = Load(direcotry + file);
        resources[file] = ResourcePtr(resource);
        return resource;
    }

protected:
    /// Loads a resource from given file.
    /// Implemented by the derived class.
    virtual T *Load(const String &filePath) = 0;

private:
    /// Directory where the resources are loaded from.
    String direcotry;
    /// Map containing the cached resources.
    ResourceMap resources;
};

#endif // __RESOURCECACHE_H__
