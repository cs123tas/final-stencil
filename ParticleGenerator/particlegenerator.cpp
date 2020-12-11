#include "particlegenerator.h"
#include <iostream>
#include "SupportCanvas3D.h"
#include "gl/textures/Texture2D.h"

ParticleGenerator::ParticleGenerator()
{

}

ParticleGenerator::ParticleGenerator(glm::mat4 modelMat, int numParticles) :
    m_modelMat(modelMat), m_numParticles(numParticles), m_evenPass(true), m_firstPass(true),
    m_particlesFBO1(nullptr), m_particlesFBO2(nullptr)
{
    loadParticleUpdateShader();
    loadParticleDrawShader();
    initializeParticleShaders();
}

void ParticleGenerator::loadParticleUpdateShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/quad.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/particles_update.frag");
    m_particleUpdateProgram = std::make_unique<CS123::GL::Shader>(vertexSource, fragmentSource);
}

void ParticleGenerator::loadParticleDrawShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/particles_draw.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/particles_draw.frag");
    m_particleDrawProgram = std::make_unique<CS123::GL::Shader>(vertexSource, fragmentSource);
}

void ParticleGenerator::initializeParticleShaders() {
//    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    std::vector<GLfloat> quadData;
    quadData = {-1, 1, 0, 0, 1, \
                -1, -1, 0, 0, 0, \
                 1, 1, 0, 1, 1, \
                 1, -1, 0, 1, 0};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();

    glGenVertexArrays(1, &m_particlesVAO);

    m_particlesFBO1 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, \
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBO2 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, \
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);

    GLint maxRenderBufferSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &maxRenderBufferSize);
    std::cout << "Max FBO size: " << maxRenderBufferSize << std::endl;
}

void ParticleGenerator::draw(Camera *camera, int width, int height, float ratio) {
    m_particleDrawProgram->bind();
    setParticleSceneUniforms(camera);
    m_particleUpdateProgram->unbind();

    glDisable(GL_CULL_FACE);
    renderParticles(width, height, ratio);
}

void ParticleGenerator::renderParticles(int width, int height, float ratio) {
    auto prevFBO = m_evenPass ? m_particlesFBO1 : m_particlesFBO2;
    auto nextFBO = m_evenPass ? m_particlesFBO2 : m_particlesFBO1;
    float firstPass = m_firstPass ? 1.0f : 0.0f;

    // TODO [Task 14] Move the particles from prevFBO to nextFBO while updating them
    nextFBO->bind();
    m_particleUpdateProgram->bind();

    glActiveTexture(GL_TEXTURE0);
    prevFBO->getColorAttachment(0).bind();

    glActiveTexture(GL_TEXTURE1);
    prevFBO->getColorAttachment(1).bind();

    m_particleUpdateProgram->setUniform("firstPass", firstPass);
    m_particleUpdateProgram->setUniform("numParticles", m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram->getID(), "prevPos"), 0);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram->getID(), "prevVel"), 1);
    m_particleUpdateProgram->setUniform("model", m_modelMat);
    m_quad->draw();

    // TODO [Task 17] Draw the particles from nextFBO
    nextFBO->unbind();
//    glClear(GL_COLOR_BUFFER_BIT);
//    glClear(GL_DEPTH_BUFFER_BIT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    m_particleDrawProgram->bind();
    glViewport(0, 0, width * ratio, height * ratio);

    glActiveTexture(GL_TEXTURE0);
    nextFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    nextFBO->getColorAttachment(1).bind();

    m_particleDrawProgram->setUniform("numParticles", m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram->getID(), "pos"), 0);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram->getID(), "vel"), 1);

    glBindVertexArray(m_particlesVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3 * m_numParticles);
    glBindVertexArray(0);

    glBlendFunc(GL_ONE, GL_ZERO);

    m_firstPass = false;
    m_evenPass = !m_evenPass;
}

void ParticleGenerator::setParticleSceneUniforms(Camera *camera) {
    m_particleDrawProgram->setUniform("p", camera->getProjectionMatrix());
    m_particleDrawProgram->setUniform("v", camera->getViewMatrix());
    m_particleDrawProgram->setUniform("m", m_modelMat);
}
