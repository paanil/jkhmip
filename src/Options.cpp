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

#include<map>
#include<string>
#include<iostream>
#include<ostream>
#include<sstream>
#include<stdlib.h>
#include<fstream>
#include "Options.h"
#include "Logger.h"

// Add string/int pair to database.
void Options::setInt(const char* key, int i) { _intData[std::string(key)] = i; }

// Add string/bool pair to database.
void Options::setBool(const char* key, bool b) { _boolData[std::string(key)] = b;}

// Add string/floast pair to database.
void Options::setFloat(const char* key, float f) { _floatData[std::string(key)] = f;}

// Add string/string pair to database.
void Options::setString(const char* key, const char* c) { _stringData[std::string(key)] = std::string(c); }


/* Parse data from a string.
 * ';' is the delimiter.
 *
 * STRING:             PARSED DATA:
 * -------------------+-------+-------+--------+
 * std::string        + type  |key    | value  |
 * -------------------+-------+-------+--------+
 * "int;Height;120"   + "int" |Height | 120    |
 * -------------------+-------+-------+--------+
 */
void Options::parseLine(const std::string &s)
{
    std::string type;
    std::string key;
    std::string value;
    std::istringstream ss( s );
    int counter = 0;
    while (!ss.eof())
    {
        std::string x;
        getline( ss, x, ';' );
        if (counter == 0)
        {
            type = x;
            counter++;
        }
        else if (counter == 1)
        {
            key = x;
            counter++;
        }
        else if (counter == 2)
        {
            value = x;
            counter++;
        }
        else if (counter > 2)
        {
            LOG_ERROR("Too many fields in string %", s);
        }
    }

    if (type == "int") setInt(key.c_str(), srtToInt(value));
    else if (type == "float") setFloat(key.c_str(), srtToFloat(value));
    else if (type == "bool") setBool(key.c_str(), srtToBool(value));
    else if (type == "string") setString(key.c_str(), value.c_str());
    else std::cout << "unknow TYPE" << type << std::endl;
}

int Options::srtToInt(const std::string &s) const
{
    std::istringstream ss( s );
    int result;
    if (!(ss >> result)) LOG_ERROR("Conversion from % to int failed", s);
    return result;
}

float Options::srtToFloat(const std::string &s) const
{
    std::istringstream ss( s );
    float result;
    if (!(ss >> result)) LOG_ERROR("Conversion from % to float failed", s);
    return result;
}

bool Options::srtToBool(const std::string &s) const
{
    std::stringstream ss;
	bool result;
	ss << std::boolalpha << s;
	ss >> std::boolalpha;
	if (!(ss >> result)) LOG_ERROR("Conversion from % to bool failed", s);
	return result;
}

/* overload the << operator for an ostream */
std::ostream& operator<<(std::ostream& os, const Options &op)
{
    for (auto it = op._intData.begin(); it!=op._intData.end(); ++it)
    {
        os << "int;" << it->first << ";" << it->second << std::endl;
    }
    for (auto it = op._boolData.begin(); it!=op._boolData.end(); ++it)
    {
        os << "bool;" << it->first << ";" << std::boolalpha << it->second << std::endl;
    }
    for (auto it = op._floatData.begin(); it!=op._floatData.end(); ++it) { os << "float;" << it->first << ";" << it->second << std::endl; }
    for (auto it = op._stringData.begin(); it!=op._stringData.end(); ++it) { os << "string;" << it->first << ";" << it->second << std::endl; }
    return os;
}

int Options::getInt(const char* key) const
{
    std::map<std::string,int>::const_iterator it = _intData.find(std::string(key));
    if (it != _intData.end()) return it->second;
    LOG_WARNING("There was no match for getInt(%).", key);
    return 0;

}

bool Options::getBool(const char* key) const
{
    std::map<std::string,bool>::const_iterator it = _boolData.find(std::string(key));
    if (it != _boolData.end()) return it->second;
    LOG_WARNING("There was no match for getBool(%).", key);
    return false;
}

float Options::getFloat(const char* key) const
{
    std::map<std::string,float>::const_iterator it = _floatData.find(std::string(key));
    if (it != _floatData.end()) return it->second;
    LOG_WARNING("There was no match for getFloat(%).", key);
    return 0.0;
}

std::string Options::getString(const char* key) const
{
    std::map<std::string,std::string>::const_iterator it = _stringData.find(std::string(key));
    if (it != _stringData.end()) return it->second;
    LOG_WARNING("There was no match for getString(%).", key);
    return "";
}

bool Options::load(const char* filename)
{
    std::ifstream file(filename);
    if (file)
    {
        for (std::string s; getline(file,s); ) parseLine(s);
        file.close();
    }
    else
    {
        LOG_ERROR("Unable to open file %.", filename);
        return false;
    }
    return true;
}

bool Options::load(const std::string &filename)
{
    return load(filename.c_str());
}

void Options::save(const std::string &filename)
{
    save(filename.c_str());
}

void Options::save(const char* filename)
{
    std::ofstream file;
    file.open (filename, std::ios::trunc);
    file << *this;
    file.close();
}

void Options::clear()
{
    _intData.clear();
    _floatData.clear();
    _boolData.clear();
    _stringData.clear();
}

void Options::copyContentToMap(Options &source)
{
    _intData.insert(source._intData.begin(), (source._intData).end());
    _boolData.insert(source._boolData.begin(), (source._boolData).end());
    _floatData.insert(source._floatData.begin(), (source._floatData).end());
    _stringData.insert(source._stringData.begin(), (source._stringData).end());
}

Options::Options()
{
    //ctor
}

Options::~Options()
{
    //dtor
}
