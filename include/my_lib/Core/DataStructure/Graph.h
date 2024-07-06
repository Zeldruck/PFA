#if !defined(GRAPH_H)
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "my_lib/Core/Maths/Mat4.h"
#include <cstdlib>
#include "Rapid_XML/rapidxml.hpp"
#include "my_lib/Physics/Transformation.h"

class Graph : public Transformation
{
public:
    Graph();
    Graph(const Vec3& _position, const Vec3& _rotation, const Vec3& _scale);
    ~Graph();
};

#endif