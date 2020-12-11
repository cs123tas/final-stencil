#include "ResourceLoader.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QGLWidget>

std::string ResourceLoader::loadResourceFileToString(const std::string &resourcePath)
{
    QString vertFilePath = QString::fromStdString(resourcePath);
    QFile vertFile(vertFilePath);
    if (vertFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream vertStream(&vertFile);
        QString contents = vertStream.readAll();
        return contents.toStdString();
    }
    throw CS123::IOException("Could not open file: " + resourcePath);
}

GLuint ResourceLoader::createShaderProgram(const char *vertexFilePath,const char *fragmentFilePath) {
    // Create and compile the shaders.
    GLuint vertexShaderID = createShader(GL_VERTEX_SHADER, vertexFilePath);
    GLuint fragmentShaderID = createShader(GL_FRAGMENT_SHADER, fragmentFilePath);

    // Link the shader program.
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderID);
    glAttachShader(programId, fragmentShaderID);
    glLinkProgram(programId);

    // Print the info log.
    GLint result = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> infoLog(std::max(infoLogLength, int(1)));
        glGetProgramInfoLog(programId, infoLogLength, NULL, &infoLog[0]);
        fprintf(stdout, "%s\n", &infoLog[0]);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programId;
}

GLuint ResourceLoader::createShader(GLenum shaderType, const char *filepath) {
    GLuint shaderID = glCreateShader(shaderType);

    // Read shader file.
    std::string code;
    QString filepathStr = QString(filepath);
    QFile file(filepathStr);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        code = stream.readAll().toStdString();
    }

    // Compile shader code.
    printf("Compiling shader: %s\n", filepath);
    const char *codePtr = code.c_str();
    glShaderSource(shaderID, 1, &codePtr, NULL);
    glCompileShader(shaderID);

    // Print info log.
    GLint result = GL_FALSE;
    int infoLogLength;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &infoLog[0]);
        fprintf(stdout, "%s\n", &infoLog[0]);
    }

    return shaderID;
}

/**
  Loads the cube map into video memory.

  @param files: a list of files containing the cube map images (should be length
  six) in order
  @return the assigned OpenGL id to the cube map
**/
GLuint ResourceLoader::loadCubeMap(QList<QFile *> files)
{
    Q_ASSERT(files.length() == 6);

    // Generate an ID
    GLuint id;
    glGenTextures(1, &id);

    // Bind the texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    // Load and build mipmaps for each image
    for (int i = 0; i < 6; ++i)
    {
        QImage image, texture;
        image.load(files[i]->fileName());
        image = image.mirrored(false, true);
        texture = QGLWidget::convertToGLFormat(image);
        texture = texture.scaledToWidth(2048, Qt::SmoothTransformation);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, texture.bits());
    }

    // Set filter when pixel occupies more than one texture element
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Set filter when pixel smaller than one texture element
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return id;
}

/**
    Creates a call list for a skybox
  **/
GLuint ResourceLoader::loadSkybox()
{
    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

    glBegin(GL_QUADS);
    float extent = 1000.f;
    glTexCoord3f( 1.0f, -1.0f, -1.0f); glVertex3f( extent, -extent, -extent);
    glTexCoord3f(-1.0f, -1.0f, -1.0f); glVertex3f(-extent, -extent, -extent);
    glTexCoord3f(-1.0f,  1.0f, -1.0f); glVertex3f(-extent,  extent, -extent);
    glTexCoord3f( 1.0f,  1.0f, -1.0f); glVertex3f( extent,  extent, -extent);

    glTexCoord3f( 1.0f, -1.0f,  1.0f); glVertex3f( extent, -extent,  extent);
    glTexCoord3f( 1.0f, -1.0f, -1.0f); glVertex3f( extent, -extent, -extent);
    glTexCoord3f( 1.0f,  1.0f, -1.0f); glVertex3f( extent,  extent, -extent);
    glTexCoord3f( 1.0f,  1.0f,  1.0f); glVertex3f( extent,  extent,  extent);

    glTexCoord3f(-1.0f, -1.0f,  1.0f); glVertex3f(-extent, -extent,  extent);
    glTexCoord3f( 1.0f, -1.0f,  1.0f); glVertex3f( extent, -extent,  extent);
    glTexCoord3f( 1.0f,  1.0f,  1.0f); glVertex3f( extent,  extent,  extent);
    glTexCoord3f(-1.0f,  1.0f,  1.0f); glVertex3f(-extent,  extent,  extent);

    glTexCoord3f(-1.0f, -1.0f, -1.0f); glVertex3f(-extent, -extent, -extent);
    glTexCoord3f(-1.0f, -1.0f,  1.0f); glVertex3f(-extent, -extent,  extent);
    glTexCoord3f(-1.0f,  1.0f,  1.0f); glVertex3f(-extent,  extent,  extent);
    glTexCoord3f(-1.0f,  1.0f, -1.0f); glVertex3f(-extent,  extent, -extent);

    glTexCoord3f(-1.0f,  1.0f, -1.0f); glVertex3f(-extent,  extent, -extent);
    glTexCoord3f(-1.0f,  1.0f,  1.0f); glVertex3f(-extent,  extent,  extent);
    glTexCoord3f( 1.0f,  1.0f,  1.0f); glVertex3f( extent,  extent,  extent);
    glTexCoord3f( 1.0f,  1.0f, -1.0f); glVertex3f( extent,  extent, -extent);

    glTexCoord3f(-1.0f, -1.0f, -1.0f); glVertex3f(-extent, -extent, -extent);
    glTexCoord3f( 1.0f, -1.0f, -1.0f); glVertex3f( extent, -extent, -extent);
    glTexCoord3f( 1.0f, -1.0f,  1.0f); glVertex3f( extent, -extent,  extent);
    glTexCoord3f(-1.0f, -1.0f,  1.0f); glVertex3f(-extent, -extent,  extent);
    glEnd();
    glEndList();
    return id;
}
