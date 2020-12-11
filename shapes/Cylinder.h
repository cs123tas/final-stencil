#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"
#include <algorithm>
#include <vector>

class Cylinder : public Shape
{
public:
    Cylinder();
    Cylinder(int param1, int param2);
    ~Cylinder();

    void setParams(int param1, int param2, float param3);

protected:
    std::vector<GLfloat> getFaceVertexData(int param1, int param2);

    int m_param1;
    int m_param2;
};

#endif // CYLINDER_H
