/*
================================================================================

Copyright (c) 2014 Janne Kauppinen
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

#ifndef CONF_H_INCLUDED
#define CONF_H_INCLUDED
#include<string>
#include "Options.h"

namespace Config
{
    /// Database for key/value pairs.
    extern Options op;
    /// Database for temporary settings.
    extern Options op_temp;
    /// File location for config file.
    extern const std::string config_file;

    /// Set default values.
    void defaultSettings();
    /// Move data from temporary database to the actual database.
    void applyChanges();
    /// Clear all data from both temporary and actual database.
    void clearData();
    /// Clear temporary data.
    void clearTemp();

    /// Load data from a file. Return false if loading fails. Else return true.
    bool loadData(const std::string &filename);

    /// Save the data to a file.
    void saveData(const std::string &filename);

    /// Set member-functios. If temp is true, the value is stored in temporary database.
    /// If temp is false, the value is stored in the actual database.
    void setInt(const char* key, int i, bool temp = false);
    void setBool(const char* key, bool b, bool temp = false);
    void setFloat(const char* key, float f, bool temp = false);
    void setString(const char* key, const char* c, bool temp = false);

    /// If no matches is found, 0 is returned.
    int getInt(const char* key);
    /// If no matches is found, false is returned.
    bool getBool(const char* key);
    /// If no matches is found, 0.0 is returned.
    float getFloat(const char* key);
    /// If no matches is found, "" is returned.
    std::string getString(const char* key);
}


#endif // CONF_H_INCLUDED
