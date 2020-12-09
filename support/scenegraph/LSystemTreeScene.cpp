#include "LSystemTreeScene.h"
#include "GL/glew.h"
#include <QGLWidget>
#include "support/camera/Camera.h"

#include "support/Settings.h"
#include "support/scenegraph/SupportCanvas3D.h"
#include "support/lib/ResourceLoader.h"
#include "support/gl/shaders/CS123Shader.h"

#include "support/shapes/Cube.h"
#include "support/shapes/Cone.h"
#include "support/shapes/Sphere.h"
#include "support/shapes/Cylinder.h"
#include "support/shapes/Torus.h"

#include <iostream>

using namespace CS123::GL;


LSystemTreeScene::LSystemTreeScene()
{
    loadPhongShader();
//    loadWireframeShader();
//    loadNormalsShader();
//    loadNormalsArrowShader();
    shapeBank.resize(6);
    LODdivisor = -1; //-1 = uninitialized, anything else is initialized (since a scene can have 0 primitives)
    defineShapeBank();
    // make a new L System visualizer
    m_lSystemViz = std::make_unique<LSystemVisualizer>();
    makeLSystemVisualizer();
    // add some lights to the scene
    CS123SceneLightData light = {0, LightType::LIGHT_POINT, glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 1), glm::vec4(1, 1, 1, 0)};
    CS123SceneLightData light2 = {0, LightType::LIGHT_POINT, glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 1), glm::vec4(-2, 1, -2, 0)};
    CS123SceneGlobalData globalLSys = {0.7f, 0.6f, 0.1f, 1};
    setGlobal(globalLSys);
    lightingInformation.push_back(light);
    lightingInformation.push_back(light2);
    setLights();
}

LSystemTreeScene::~LSystemTreeScene()
{
}

void LSystemTreeScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

//void SceneviewScene::loadWireframeShader() {
//    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.vert");
//    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.frag");
//    m_wireframeShader = std::make_unique<Shader>(vertexSource, fragmentSource);
//}

//void SceneviewScene::loadNormalsShader() {
//    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.vert");
//    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normals.gsh");
//    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.frag");
//    m_normalsShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
//}

//void SceneviewScene::loadNormalsArrowShader() {
//    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.vert");
//    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.gsh");
//    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.frag");
//    m_normalsArrowShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
//}

void LSystemTreeScene::render(SupportCanvas3D *context) {
    setLOD();
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Phong pass
    m_phongShader->bind();
    setPhongSceneUniforms(context);
    setLights();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderGeometry(PHONG);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();


//    //Wireframe pass
//    if (settings.drawWireframe) {
//        m_wireframeShader->bind();
//        setMatrixUniforms(m_wireframeShader.get(), context);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        renderGeometry(WIREFRAME);
//        m_wireframeShader->unbind();
//    }

//    //Normals pass
//    if (settings.drawNormals) {
//        // Render the lines.
//        m_normalsShader->bind();
//        setMatrixUniforms(m_normalsShader.get(), context);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        renderGeometry(NORMAL_LINE);
//        m_normalsShader->unbind();

//        // Render the arrows.
//        m_normalsArrowShader->bind();
//        setMatrixUniforms(m_normalsArrowShader.get(), context);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//        renderGeometry(NORMAL_ARROW);
//        m_normalsArrowShader->unbind();
//    }

}

void LSystemTreeScene::setPhongSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", settings.useLighting);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

void LSystemTreeScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
    shader->setUniform("v", context->getCamera()->getViewMatrix());
}

void LSystemTreeScene::setLights()
{
    int size = lightingInformation.size();
    for (int i = 0; i < size; i++){
        m_phongShader->setLight(lightingInformation[i]);
    }
}

void LSystemTreeScene::renderGeometry(RENDERING_PASS pass) {
    int size = primitives.size();
    for (int i = 0; i < size; i++){
        CS123ScenePrimitiveBundle bundle = primitives[i];
        CS123SceneMaterial mat = bundle.primitive.material;
        mat.cDiffuse *= globalData.kd;
        mat.cAmbient *= globalData.ka;
        mat.shininess *= globalData.ks;
        mat.cTransparent *= globalData.kt;

        switch (pass) {
            case PHONG:
                m_phongShader->setUniform("m", bundle.model);
                m_phongShader->applyMaterial(mat);
                break;
            case WIREFRAME:
                m_wireframeShader->setUniform("m", bundle.model);
                break;
            case NORMAL_LINE:
                m_normalsShader->setUniform("m", bundle.model);
                break;
            case NORMAL_ARROW:
                m_normalsArrowShader->setUniform("m", bundle.model);
                break;
        }


        (shapeBank[(int) bundle.primitive.type])->draw();
    }
}

void LSystemTreeScene::settingsChanged() {
    // make a new LSystem with the current settings
    m_lSystemViz = std::make_unique<LSystemVisualizer>();
    makeLSystemVisualizer();
    // std::cout << "the settings were chnanged" << std::endl;
    // std::cout << settings.lengthStochasticity << std::endl;
    renderGeometry(PHONG);
}

void LSystemTreeScene::setLOD() {
    if (primitiveCount == -1) return; //Scene hasn't finished loading yet
    LODdivisor = pow(primitiveCount, 0.5) - 2; //https://www.desmos.com/calculator/jdgphtltcc (my own func)
    if (LODdivisor < 1) LODdivisor = 1;
    if (LODdivisor > 15) LODdivisor = 15;
}

void LSystemTreeScene::defineShapeBank(){
    int p1 = std::floor(settings.shapeParameter1 / std::max(1.f, LODdivisor));
    int p2 = std::floor(settings.shapeParameter2 / std::max(1.f, LODdivisor));
    int p3 = std::floor(settings.shapeParameter3 / std::max(1.f, LODdivisor));
    shapeBank[0] = std::make_unique<Cube>(p1);
    shapeBank[1] = std::make_unique<Cone>(p1, p2);
    shapeBank[2] = std::make_unique<Cylinder>(p1, p2);
    shapeBank[3] = std::make_unique<Torus>(p1, p2, p3);
    shapeBank[4] = std::make_unique<Sphere>(p1, p2);
    shapeBank[5] = std::make_unique<Sphere>(p1, p2); //Speres will substitite for meshes for now
}

void LSystemTreeScene::makeLSystemVisualizer() {
    int numCyls = m_lSystemViz->getNumCyls();
    CS123SceneMaterial material;
    material.clear();
    material.cAmbient.r = 0.2f;
    material.cAmbient.g = 0.1f;
    material.cDiffuse.r = 1.0f;
    material.cDiffuse.g = 0.5f;
    material.cSpecular.r = material.cSpecular.g = material.cSpecular.b = 0.3;
    material.shininess = 12;
    // if seaweed, make material green
    if(settings.lSystemType == 1) {
        material.cAmbient.r = 0.04f;
        material.cAmbient.g = 0.2f;
        material.cAmbient.b = 0.04f;
        material.cDiffuse.r = 0.2f;
        material.cDiffuse.b = 0.4f;
    }
    primitives.clear();
    // add all cylinders to scene
    CS123ScenePrimitive cyl = {PrimitiveType::PRIMITIVE_CYLINDER, std::string(), material};
    for(int i = 0; i < numCyls; i++) {
        // make a new scene primitive
        addPrimitive(cyl, m_lSystemViz->getTransformationMatrix(i));

    }
}