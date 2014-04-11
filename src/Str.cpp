
#include "Str.h"

#include <cctype>

bool StrIEquals(const String &str1, const String &str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }

    const char *s1 = str1.c_str();
    const char *s2 = str2.c_str();

    for (; *s1 && *s2; s1++, s2++)
    {
        if (tolower(*s1) != tolower(*s2))
        {
            return false;
        }
    }
    return true;
}
