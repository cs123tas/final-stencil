#ifndef SHAPE_H
#define SHAPE_H

/** imports the OpenGL math library https://glm.g-truc.net/0.9.2/api/a00001.html */
#include <glm/glm.hpp>
#include "GL/glew.h"

#include<memory>
#include <vector>
#include <cmath>

const float RADIUS = 0.5f;

/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
inline void insertVec3(std::vector<float> &data, glm::vec3 v){
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

namespace CS123 { namespace GL {
class VAO;
}}

class Shape
{
public:
    Shape();
    virtual ~Shape();
    void draw();

    void setShapeType(int type);
    int getShapeType();
    void setShapeParameter1(int param1);
    int getShapeParameter1();
    void setShapeParameter2(int param2);
    int getShapeParameter2();
    void setShapeParameter3(float param3);
    float getShapeParameter3();
    virtual void setParams(int param1, int param2, float param3);
    virtual std::vector<GLfloat> getFaceVertexData(int param1, int param2);
    std::vector<GLfloat> getVertexData();

protected:
    /** builds the VAO, pretty much the same as from lab 1 */
    void buildVAO();

    // generate the normalized normal vector given a triangle
    glm::vec3 getNormalVec(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
    // generate a circle along y axis
    std::vector<GLfloat> getCircleVertexData(bool isBottom, int param1, int param2);
    std::vector<GLfloat> getSectorVertexData(const std::vector<GLfloat>& vertexCoordinates,
                                             int param1,
                                             const glm::vec3& normal,
                                             const glm::vec3& lAverageNormal,
                                             const glm::vec3& rAverageNormal);

    std::vector<GLfloat> m_vertexData;
    std::unique_ptr<CS123::GL::VAO> m_VAO;

    // used for comparision with settings
    int m_shapeType;
    int m_shapeParameter1;
    int m_shapeParameter2;
    float m_shapeParameter3;
};

#endif // SHAPE_H
