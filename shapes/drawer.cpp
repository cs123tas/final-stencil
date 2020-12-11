#include "shapes/drawer.h"
#include "lib/ResourceLoader.h"
#include "glm/gtx/transform.hpp"
#include <iostream>
#include "gl/textures/Texture2D.h"
#include "Settings.h"
#include "gl/GLDebug.h"

using namespace CS123::GL;

Drawer::Drawer()
{
    m_shapePtr = std::make_unique<Cylinder>(PARAM1, PARAM2);

    initializeParticleGenerators();

    loadPhongShader();
    loadSkyBoxShader();
    createLights();

    // setting up global data
    m_global_data.ka = 0.8;
    m_global_data.kd = 0.5;
    m_global_data.ks = 0.5;

    m_count = 0;
}


Drawer::~Drawer() {
}

void Drawer::setData(const std::vector<SegmentData>& data) {
    for (unsigned long i = 0; i < m_data.size(); i++) {
        delete(m_data[i].particleGenerator);
    }
    m_data = data;
    initializeParticleGenerators();
}

void Drawer::initializeParticleGenerators(){
    std::cout << m_data.size() << std::endl;
    for (unsigned long i = 0; i < m_data.size(); i++) {
        m_data[i].particleGenerator = new ParticleGenerator(m_data[i].matrix, m_numParticles);
    }
}

void Drawer::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void Drawer::loadSkyBoxShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/skybox.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/skybox.frag");
    m_skyBoxShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);

    // load images (y seems to be upside down here)
    m_textures_faces.push_back(":/skybox/images/posx.jpg");
    m_textures_faces.push_back(":/skybox/images/negx.jpg");
    m_textures_faces.push_back(":/skybox/images/negy.jpg");
    m_textures_faces.push_back(":/skybox/images/posy.jpg");
    m_textures_faces.push_back(":/skybox/images/posz.jpg");
    m_textures_faces.push_back(":/skybox/images/negz.jpg");

    m_cubemapTexture = loadCubemap(m_textures_faces);

    m_skybox_cube = std::make_unique<OpenGLShape>();
    m_skybox_cube->setVertexData(&skyboxVertices[0], sizeof(skyboxVertices), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, 36);
    m_skybox_cube->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_skybox_cube->buildVAO();
}

void Drawer::createLights() {
    m_light_data = {};

    CS123SceneLightData ptLight1;
    ptLight1.id = 0;
    ptLight1.pos = glm::vec4(3, 3, 3, 1);

    // these two are not used yet but we can use if we implement phong's on our own ... not the sceneview way
    ptLight1.color = glm::vec4(1, 1, 1, 1);
    ptLight1.function = glm::vec3();

    m_light_data.push_back(ptLight1);

}

std::vector<GLfloat> Drawer::vertexTimesMatrix(const glm::mat4& matrix, const std::vector<GLfloat>& vertexData) {
    // first three is location, last three is normal
    assert(vertexData.size() %6 == 0);

    std::vector<GLfloat> result;
    for (size_t i = 0; i < vertexData.size(); i += 6) {
        // get world space location
        glm::vec4 loc = glm::vec4(vertexData[i], vertexData[i + 1], vertexData[i + 2], 1.);
        loc = matrix * loc;
        insertVec3(result, loc.xyz());

        // get world-space normal
        glm::vec3 normal = glm::vec3(vertexData[i + 3], vertexData[i + 4], vertexData[i + 5]);
        glm::mat3 m = glm::mat3(matrix); // extract the 3x3 matrix
        normal = glm::transpose(glm::inverse(m)) * normal; // no need to translate ?
        insertVec3(result, glm::normalize(normal));

        // texture mapping (if any)
    }

    return result;
}

void Drawer::render(SupportCanvas3D *context) {
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    // draw skybox
    m_skyBoxShader->bind();
    setSkyBoxUniforms(context);
    initializeSkybox();
    m_skyBoxShader->unbind();

    m_phongShader->bind();
    setTreeSceneUniforms(context);
    setLights();
    draw(m_data); // prime function here
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();

    glDisable(GL_CULL_FACE);
    if (settings.burnTree) {
        for (unsigned long i = 0; i < m_data.size(); i++) {
            m_data[i].particleGenerator->draw(context->getCamera(), context->width(), context->height(), context->m_ratio);
        }
    }
    context->update();
}

void Drawer::setSkyBoxUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_skyBoxShader->setUniform("view", camera->getViewMatrix());
    m_skyBoxShader->setUniform("projection", camera->getProjectionMatrix());
    m_skyBoxShader->setUniform("scale", SKYBOX_LENGTH);
}

void Drawer::setTreeSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", true);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}


void Drawer::setLights()
{
    for (auto light : this->m_light_data)
        m_phongShader->setLight(light);
}

void Drawer::draw(const std::vector<SegmentData>& segmentData) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (SegmentData data : segmentData) {
        // set up the material here ?
        CS123SceneMaterial material;

        material.cAmbient = glm::vec4(0.3, 0.3, 0.2, 1.);
        material.cDiffuse = glm::vec4(1., 1., 1., 1.);
        material.cSpecular = glm::vec4(0., 0., 0., 1.);
        material.cAmbient *= m_global_data.ka;
        material.cDiffuse *= m_global_data.kd;

        m_phongShader->applyMaterial(material);

        // set as model matrix (transforming on GPU)
        m_phongShader->setUniform("m", data.matrix);

        m_shapePtr->draw();
    }

    return ;
}

void Drawer::initializeSkybox() {
    glDepthMask(GL_FALSE);

    GLuint VAO = m_skybox_cube->getHandle();
    GLuint VBO;

    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices) / sizeof(float), skyboxVertices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, (GLvoid*) NULL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Disable the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}

unsigned int Drawer::loadCubemap(const vector<std::string>& faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    if (textureID) {
        glDeleteTextures(1, &textureID);
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glGenerateMipmap(GL_TEXTURE_2D);

    int width, height;
    unsigned char *data;
    for(unsigned int i = 0; i < faces.size(); i++)
    {
        QImage image;
        image.load(QString(faces[i].c_str()));
        //image = image.mirrored(false, true);
        QImage oglFormat = QGLWidget::convertToGLFormat(image);
        data = oglFormat.bits();
        width = oglFormat.width();
        height = oglFormat.height();

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void Drawer::settingsChanged() {
    // reset any parameters used in drawing things here
    m_numParticles = 16384;
}
