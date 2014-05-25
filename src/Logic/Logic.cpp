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

#include "Logic.h"
#include "CameraController.h"
#include "Rotator.h"

CameraController *Logic::CreateCameraController()
{
    CameraController *cameraController = new CameraController();
    AddLogic(cameraController);
    return cameraController;
}

Rotator *Logic::CreateRotator()
{
    Rotator *rotator = new Rotator();
    AddLogic(rotator);
    return rotator;
}

void Logic::Update(float dt)
{
    for (LogicPtr &logic : logics)
    {
        logic->Update(dt);
    }
}

void Logic::AddLogic(LogicBase *logic)
{
    logics.push_back(LogicPtr(logic));
}
