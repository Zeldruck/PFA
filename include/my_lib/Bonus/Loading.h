#if !defined(LOADING_H)
#define LOADING_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "my_lib/Core/Debug/Log.h"

enum InfluenceEnum
{
    Huge   = 0,
    Large  = 1,
    Small  = 2,
};

namespace Loading
{
    void Print(InfluenceEnum influence, std::string step);
} // namespace name


#endif // LOADING_H
