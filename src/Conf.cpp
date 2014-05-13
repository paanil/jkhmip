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

#include<string>
#include "Conf.h"
#include "Logger.h"

/// Container for "all" the various global application options
/// and customizable settings.

namespace Config
{
    /// Database for key/pair kind of data.
    Options op;
    /// For temporary data.
    Options op_temp;
    /// The configure file.
    const std::string config_file("Data/render.opt");

    int getInt(const char* key) { return op.getInt(key); }
    bool getBool(const char* key) { return op.getBool(key); }
    float getFloat(const char* key) { return op.getFloat(key); }
    std::string getString(const char* key) { return op.getString(key); }

    void setInt(const char* key, int i, bool temp)
    {
        if (temp) op_temp.setInt(key,i);
        else op.setInt(key,i);
    }
    void setBool(const char* key, bool b, bool temp)
    {
        if (temp) op_temp.setBool(key,b);
        else op.setBool(key,b);
    }
    void setFloat(const char* key, float f, bool temp)
    {
        if (temp) op_temp.setFloat(key,f);
        else op.setFloat(key,f);
    }
    void setString(const char* key, const char* c, bool temp)
    {
        if (temp) op_temp.setString(key,c);
        else op.setString(key,c);
    }

    void applyChanges()
    {
        op.copyContentToMap(op_temp);
        clearTemp();
    }

    void clearData()
    {
        op.clear();
        clearTemp();
    }

    void clearTemp() { op_temp.clear(); }

    /* Put here the default settings */
    void defaultSettings()
    {
        /// The main window
        clearData();
        op.setInt("mainScreen_Width", 1280);
        op.setInt("mainScreen_Height", 720);
        op.setBool("mainScreen_FullScreen", false);
        op.setBool("mainScreen_vsync", true);

        /// File locations
        op.setString("Shader_location", "Data/Shaders/");
        op.setString("Texture_location", "Data/Textures/");
        op.setString("Material_location", "Data/Materials/");
        op.setString("Model_location", "Data/Models/");
        op.setString("Font_location", "Data/Fonts/");
        op.setString("Scene_location", "Data/Scenes/");
    }

    bool loadData(const std::string &filename)
    {
        LOG_INFO("Loading configuration settings '%'...", filename);
        clearData();
        // Make backup from data.
        // op_temp.copyContentToMap(op);
        // op.clear();
        if (op.load(filename)) return true;
        // LOG ERROR
        // Restore data.
        // op.clear();
        // op.copyContentToMap(op_temp);
        // clearTemp();
        return false;
    }

    void saveData(const std::string &filename)
    {
        LOG_INFO("Saving configuration settings '%'...", filename);
        op.save(filename);
    }

}

