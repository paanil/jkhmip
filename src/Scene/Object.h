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

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Node.h"

class Model;
class RenderCommandList;

namespace Scene
{

    /// Renderable object node.
    ///
    class Object : public Node
    {
    public:
        /// Sets model to 0.
        Object();

        /// Sets model.
        void SetModel(Model *model);

        /// Adds model to the list of render commands.
        void GetRenderCommands(RenderCommandList &commands);

    private:
        Model *model;
    };

} // Scene

#endif // __OBJECT_H__
