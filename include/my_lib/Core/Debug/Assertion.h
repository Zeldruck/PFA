#if !defined(ASSERTION_H)
#define ASSERTION_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define black_      "\033[0;30m"
#define red_        "\033[0;31m"
#define green_      "\033[0;32m"
#define yellow_     "\033[0;33m"
#define blue_       "\033[0;34m"
#define magenta_    "\033[0;35m"
#define cyan_       "\033[0;36m"
#define white_      "\033[0;37m"
#define reset_      "\033[0;0m"
#define bright_     "\033[1;0m"
#define underline_  "\033[4;0m"

#ifdef NDEBUG
#define myAssert(condition) ((void)0)
#else
#define myAssert(condition) if (!(condition)) {std::cout << red_  << "Assert: " << cyan_ << "in file : " << __FILE__ << "; line : " << __LINE__ << ";" << magenta_ << " condition failed !" << yellow_  << " aborting..." << black_  << std::endl; abort();}
#endif

#endif // ASSERTION_H