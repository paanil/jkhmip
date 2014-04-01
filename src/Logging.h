
#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <cstdio>

/// Logging uses printf for now.
/// Examples:
///
/// int dataSize = 1024;
/// LOG_INFO("Data size: %d", dataSize);
///
/// LOG_DEBUG("Hello %s!", "world");
///
/// std::string fileName("file.xyz");
/// LOG_WARNING("File '%s' not found.", fileName.c_str());
///
/// More about formatting: http://www.cplusplus.com/reference/cstdio/printf/

//TODO: replace printf using c++11 templates

#define LOG_INFO(...)       do { printf("INFO     "); printf(__VA_ARGS__); printf("\n"); } while(0)
#define LOG_DEBUG(...)      do { printf("DEBUG    "); printf(__VA_ARGS__); printf("\n"); } while(0)
#define LOG_WARNING(...)    do { printf("WARNING  "); printf(__VA_ARGS__); printf("\n"); } while(0)
#define LOG_ERROR(...)      do { printf("ERROR    "); printf(__VA_ARGS__); printf("\n"); } while(0)

#endif // __LOGGING_H__
