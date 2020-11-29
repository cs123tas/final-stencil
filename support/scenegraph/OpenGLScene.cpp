#include "OpenGLScene.h"

#include <GL/glew.h>

#include "support/Settings.h"

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::setClearColor() {
    if (settings.drawWireframe || settings.drawNormals) {
        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    } else {
        glClearColor(0, 0, 0, 0);
    }
}

void OpenGLScene::settingsChanged() {

}
