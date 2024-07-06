#include "my_lib/Core/Debug/Log.h"

GLenum Log::glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

void Log::Error(const char* file, int line)
{
    std::cout << "In file included from " << file << ":" <<std::endl;
    std::cout << "line(" << line << ")" ;
}

#define error() Log::Error(__FILE__,__LINE__)

void Log::PrintError(SeverityEnum severity, std::string function, std::string message)
{
    error();
    switch (severity)
    {
        case High:      std::cout << red_  << " Critical_Error: " << reset_ << "in function : " << cyan_ << function << " : " << green_  << message << reset_ << ", aborting..." << std::endl; abort(); break;
        case Medium:    std::cout << yellow_  << " Error: " << reset_ << "in function : " << cyan_ << function << " : " << green_  << message << reset_ << ", aborting..." << std::endl; abort(); break;
        case Low:       std::cout << magenta_ << " Warning: " << reset_ << "in function : " << cyan_ << function << " : " << green_  << message << std::endl; break;
    } std::cout << std::endl;
}