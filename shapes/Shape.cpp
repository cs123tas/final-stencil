#include "Shape.h"
#include "gl/datatype/VAO.h"
#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"
#include "gl/shaders/ShaderAttribLocations.h"

using namespace CS123::GL;

//Shape::Shape() :
    //m_VAO(nullptr)
Shape::Shape()
{
    m_shapeType = -1;
    m_shapeParameter1 = 0;
    m_shapeParameter2 = 0;
    m_shapeParameter3 = 0.f;
}

Shape::~Shape()
{
}

void Shape::draw() {
    if (m_VAO) {
        m_VAO->bind();
        m_VAO->draw();
        m_VAO->unbind();
    }
}

void Shape::buildVAO() {
    const int numFloatsPerVertex = 6;
    const int numVertices = m_vertexData.size() / numFloatsPerVertex;

    std::vector<VBOAttribMarker> markers;
    markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3*sizeof(float)));
    VBO vbo = VBO(m_vertexData.data(), m_vertexData.size(), markers);
    m_VAO = std::make_unique<VAO>(vbo, numVertices);
}

void Shape::setShapeType(int type) {
    m_shapeType = type;
}

int Shape::getShapeType() {
    return m_shapeType;
}

void Shape::setShapeParameter1(int param1) {
    m_shapeParameter1 = param1;
}

int Shape::getShapeParameter1() {
    return m_shapeParameter1;
}

void Shape::setShapeParameter2(int param2) {
    m_shapeParameter2 = param2;
}

int Shape::getShapeParameter2() {
    return m_shapeParameter2;
}

void Shape::setShapeParameter3(float param3) {
    m_shapeParameter3 = param3;
}

float Shape::getShapeParameter3() {
    return m_shapeParameter3;
}

/**
 * Generate the normalized normal vector given a triangle
 * Making the assumption that points are counter clockwise
 * Don't use points on the same line!
 */
glm::vec3 Shape::getNormalVec(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3) {
    glm::vec3 vector1 = point2 - point1;
    glm::vec3 vector2 = point3 - point1;
    return glm::normalize(glm::cross(vector1, vector2));
}

void Shape::setParams(int param1, int param2, float param3) {
}

std::vector<GLfloat> Shape::getFaceVertexData(int param1, int param2) {
    std::vector<GLfloat> null;
    return null;
}

std::vector<GLfloat> Shape::getCircleVertexData(bool isBottom, int param1, int param2) {
    float y;
    if (isBottom) {
        y = -RADIUS;
    } else {
        y = RADIUS;
    }

    // set the range of m_param1 to [1, 100]
    param1 = std::max(1, param1);
    param1 = std::min(100, param1);

    // set the range of m_param2 to [3, 100]
    param2 = std::max(3, param2);
    param2 = std::min(100, param2);

    float theta = 0.f;
    const float thetaDelta = 2.f * M_PI / param2;

    std::vector<GLfloat> result;
    std::vector<std::vector<GLfloat>> vertexCoordinatesVector;
    std::vector<glm::vec3> vectorNormal;

    for (int sector = 0; sector < param2; sector++) {
        float newTheta = theta + thetaDelta;
        // store the coordinates of the vertex
        std::vector<GLfloat> vertexCoordinates;

        if (isBottom) {
            for (int i = 0; i <= param1; i++) {
                float r = RADIUS * i / param1;
                insertVec3(vertexCoordinates, glm::vec3(-sin(theta) * r, -RADIUS, cos(theta) * r));
            }
            for (int i = 1; i <= param1; i++) {
                float r = RADIUS * i / param1;
                insertVec3(vertexCoordinates, glm::vec3(-sin(newTheta) * r, -RADIUS, cos(newTheta) * r));
            }
        } else {
            for (int i = 0; i <= param1; i++) {
                float r = RADIUS * i / param1;
                insertVec3(vertexCoordinates, glm::vec3(-sin(newTheta) * r, RADIUS, cos(newTheta) * r));
            }
            for (int i = 1; i <= param1; i++) {
                float r = RADIUS * i / param1;
                insertVec3(vertexCoordinates, glm::vec3(-sin(theta) * r, RADIUS, cos(theta) * r));
            }
        }
        vertexCoordinatesVector.push_back(vertexCoordinates);

        // to get normal is a bit tricky
        glm::vec3 normal = getNormalVec(glm::vec3(vertexCoordinates[0], vertexCoordinates[1], vertexCoordinates[2]),
                glm::vec3(vertexCoordinates[3], vertexCoordinates[4], vertexCoordinates[5]),
                glm::vec3(vertexCoordinates[3 * param1 + 3],
                               vertexCoordinates[3 * param1 + 4],
                            vertexCoordinates[3 * param1 + 5]));
        vectorNormal.push_back(normal);

        theta += thetaDelta;
    }

    for (int sector = 0; sector < param2; sector++) {
        // calculate average normal
        glm::vec3 normal = vectorNormal[sector];
        glm::vec3 lNormal = vectorNormal[(sector + 1) % param2];
        glm::vec3 rNormal = vectorNormal[(sector + param2 - 1) % param2];

        // take the average of two surfaces' normals
        glm::vec3 lAverage = glm::normalize(normal + lNormal);
        glm::vec3 rAverage = glm::normalize(normal + rNormal);

        std::vector<GLfloat> sectorResult = getSectorVertexData(vertexCoordinatesVector[sector], param1, normal, lAverage, rAverage);
        result.insert(result.end(), sectorResult.begin(), sectorResult.end());
    }

    return result;
}

std::vector<GLfloat> Shape::getSectorVertexData(const std::vector<GLfloat>& vertexCoordinates,
                                                int param1,
                                                const glm::vec3& normal,
                                                const glm::vec3& lAverage,
                                                const glm::vec3& rAverage) {
    std::vector<GLfloat> result;

    // the special one
    insertVec3(result,  glm::vec3(vertexCoordinates[0], vertexCoordinates[1], vertexCoordinates[2]));
    insertVec3(result, normal);
    insertVec3(result,  glm::vec3(vertexCoordinates[3], vertexCoordinates[4], vertexCoordinates[5]));
    insertVec3(result, rAverage);
    insertVec3(result,  glm::vec3(vertexCoordinates[3 * param1 + 3],
               vertexCoordinates[3 * param1 + 4],
            vertexCoordinates[3 * param1 + 5]));
    insertVec3(result, lAverage);

    for (int i = 1; i < param1; i++) {
        // one half
        insertVec3(result, glm::vec3(vertexCoordinates[3 * i],
                   vertexCoordinates[3 * i + 1],
                vertexCoordinates[3 * i + 2]));
        insertVec3(result, rAverage);

        insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 3],
                   vertexCoordinates[3 * i + 4],
                vertexCoordinates[3 * i + 5]));
        insertVec3(result, rAverage);

        insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 3 * param1],
                   vertexCoordinates[3 * i + 3 * param1 + 1],
                vertexCoordinates[3 * i + 3 * param1 + 2]));
        insertVec3(result, lAverage);

        // another half
        insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 3],
                   vertexCoordinates[3 * i + 4],
                vertexCoordinates[3 * i + 5]));
        insertVec3(result, rAverage);

        insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 3 * param1 + 3],
                   vertexCoordinates[3 * i + 3 * param1 + 4],
                vertexCoordinates[3 * i + 3 * param1 + 5]));
        insertVec3(result, lAverage);

        insertVec3(result, glm::vec3(vertexCoordinates[3 * i + 3 * param1],
                   vertexCoordinates[3 * i + 3 * param1 + 1],
                vertexCoordinates[3 * i + 3 * param1 + 2]));
        insertVec3(result, lAverage);
    }

    return result;
}

std::vector<GLfloat> Shape::getVertexData() {
    return m_vertexData;
}
