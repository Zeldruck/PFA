#if !defined(LOG_H)
#define LOG_H

#include "my_lib/Core/Debug/Assertion.h"

enum SeverityEnum
{
    High    = 0,
    Medium  = 1,
    Low     = 2,
};

namespace Log
{
    GLenum glCheckError_(const char *file, int line);
    void Error(const char* file, int line);
    void PrintError(SeverityEnum severity, std::string function, std::string message);
    
} // namespace Log

#define glCheckError() Log::glCheckError_(__FILE__, __LINE__)

#endif // LOG_H
