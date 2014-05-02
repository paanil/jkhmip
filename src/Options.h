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

#ifndef OPTIONS_H
#define OPTIONS_H
#include<map>
#include<string>
#include<ostream>


class Options
{
    public:
        Options();
        virtual ~Options();

        void setInt(const char* key, int i);
        void setBool(const char* key, bool b);
        void setFloat(const char* key, float f);
        void setString(const char* key, const char* c);

        /// If no matches is found, 0 is returned.
        int getInt(const char* key) const;
        /// If no matches is found, false is returned.
        bool getBool(const char* key) const;
        /// If no matches is found, 0.0 is returned.
        float getFloat(const char* key) const;
        /// If no matches is found, "" is returned.
        std::string getString(const char* key) const;

        friend std::ostream& operator<<(std::ostream &os, const Options &op);

        /// Copy data from source Options object to this object.
        void copyContentToMap(Options &source);

        /// Load data from a file. Return false if loading fails. Else return true.
        bool load(const char* filename);
        bool load(const std::string &filename);

        /// Save the data to a file.
        void save(const char* filename);
        void save(const std::string &filename);

        /// Clear all data from database.
        void clear();

    private:
        /// The data.
        std::map<const std::string,int> _intData;
        std::map<const std::string,bool> _boolData;
        std::map<const std::string,float> _floatData;
        std::map<const std::string,std::string> _stringData;

        /// Parse data from a string.
        void parseLine(const std::string &s);

        /// Converts string to int. If error occurs, 0 is returned.
        int srtToInt(const std::string &s) const;

        /// Converts string to float. If error occurs, 0.0 is returned.
        float srtToFloat(const std::string &s) const;

        /// Converts string to bool. If error occurs, false is returned.
        bool srtToBool(const std::string &s) const;
};

#endif // OPTIONS_H
