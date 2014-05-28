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

#include "Application.h"
#include "Logger.h"
#include "Conf.h"

#include <iostream>

/// Main function.
/// Creates an instance of Application,
/// initializes it and runs it.
int main(int argc, char **argv)
{

#ifdef RE_DEBUG
    Logger::Debug().SetStream(&std::cout);
    Logger::Debug().SetPrefix("DEBUG    ");
#endif // RE_DEBUG

    Logger::Info().SetStream(&std::cout);
    Logger::Info().SetPrefix("INFO     ");
    Logger::Warning().SetStream(&std::cout);
    Logger::Warning().SetPrefix("WARNING  ");
    Logger::Error().SetStream(&std::cout);
    Logger::Error().SetPrefix("ERROR    ");
    Config::defaultSettings();

    Application app;

    if (!app.Init("Test Application"))
    {
        return 0;
    }

    app.Run();

    return 0;
}
