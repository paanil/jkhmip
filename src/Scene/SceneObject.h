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

#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__

#include "SceneNode.h"

class Model;
class RenderCommandList;

/// Renderable object node.
///
class SceneObject : public SceneNode
{
public:
    /// Sets model to 0.
    SceneObject();

    /// Sets model.
    void SetModel(Model *mdl);

    /// Adds model to the list of render commands.
    void GetRenderCommands(RenderCommandList &commands);

private:
    Model *model;
};

#endif // __SCENEOBJECT_H__
