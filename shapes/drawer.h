#ifndef DRAWER_H
#define DRAWER_H

#include "GL/glew.h"
#ifdef __APPLE__
#include <glu.h>
#else
#include "GL/glu.h"
#endif

#include <vector>
#include <glm.hpp>
#include <memory>
#include "camera/Camera.h"
#include "scenegraph/OpenGLScene.h"
#include "shapes/Shape.h"
#include "shapes/Cylinder.h"
#include "gl/shaders/CS123Shader.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include "gl/openglshape.h"
#include "L_System/turtle.h"
#include "ui/SupportCanvas3D.h"
#include "gl/datatype/FBO.h"

namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
}}

class SupportCanvas3D;

class Drawer : public OpenGLScene {
public:
    Drawer();
    ~Drawer();

    void setData(const std::vector<SegmentData>& data);
    void render(SupportCanvas3D *context);
    void settingsChanged();
    void draw(const std::vector<SegmentData>& data);

protected:
    /** ID for the shader program. */
    GLuint m_program;
    std::vector<SegmentData> m_data;
    std::unique_ptr<OpenGLShape> m_shape;
    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    int m_shapeParameter1;
    int m_shapeParameter2;

private:
    int m_width;
    int m_height;
    int m_numParticles;
    std::unique_ptr<CS123::GL::Shader> m_skyBoxShader;
    std::unique_ptr<OpenGLShape> m_skybox_cube;
    std::vector<std::string> m_textures_faces;
    unsigned int m_cubemapTexture;
    std::unique_ptr<Shape> m_shapePtr;

    static std::vector<GLfloat> vertexTimesMatrix(const glm::mat4& matrix, const std::vector<GLfloat>& vertexData);
    void loadPhongShader();
    void initializeParticleGenerators();
    void loadSkyBoxShader();
    void createLights();
    void setTreeSceneUniforms(SupportCanvas3D *context);
    void setSkyBoxUniforms(SupportCanvas3D *context);
    void setLights();

    void initializeSkybox();
    unsigned int loadCubemap(const vector<std::string>& faces);

    int m_count = 0;
};

static float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,
          1.0f, -1.0f, -1.0f,
          1.0f, -1.0f, -1.0f,
          1.0f,  1.0f, -1.0f,
         -1.0f,  1.0f, -1.0f,

         -1.0f, -1.0f,  1.0f,
         -1.0f, -1.0f, -1.0f,
         -1.0f,  1.0f, -1.0f,
         -1.0f,  1.0f, -1.0f,
         -1.0f,  1.0f,  1.0f,
         -1.0f, -1.0f,  1.0f,

          1.0f, -1.0f, -1.0f,
          1.0f, -1.0f,  1.0f,
          1.0f,  1.0f,  1.0f,
          1.0f,  1.0f,  1.0f,
          1.0f,  1.0f, -1.0f,
          1.0f, -1.0f, -1.0f,

         -1.0f, -1.0f,  1.0f,
         -1.0f,  1.0f,  1.0f,
          1.0f,  1.0f,  1.0f,
          1.0f,  1.0f,  1.0f,
          1.0f, -1.0f,  1.0f,
         -1.0f, -1.0f,  1.0f,

         -1.0f,  1.0f, -1.0f,
          1.0f,  1.0f, -1.0f,
          1.0f,  1.0f,  1.0f,
          1.0f,  1.0f,  1.0f,
         -1.0f,  1.0f,  1.0f,
         -1.0f,  1.0f, -1.0f,

         -1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f,  1.0f,
          1.0f, -1.0f, -1.0f,
          1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f,  1.0f,
          1.0f, -1.0f,  1.0f
};



#endif // DRAWER_H
