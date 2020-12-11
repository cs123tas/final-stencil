#ifndef SCENE_H
#define SCENE_H

#include "lib/CS123SceneData.h"
#include <QImage>

class Camera;
class CS123ISceneParser;


/**
 * @class Scene
 *
 * @brief This is the base class for all scenes. Modify this class if you want to provide
 * common functionality to all your scenes.
 */

/**
 * @brief The PrimitiveData struct holds data to be passed to Sceneview
 */
struct PrimitiveData {
    glm::mat4 CMTM;
    PrimitiveType objectType;
    CS123SceneColor dColor;
    CS123SceneColor aColor;
    CS123SceneColor sColor;
    CS123SceneColor rColor;
    float shininess;
    CS123SceneFileMap texture;
    float blend;
    QImage loadedText;

    PrimitiveData(glm::mat4 cum_trans_mat, PrimitiveType objectType, CS123SceneColor dColor, CS123SceneColor aColor, CS123SceneColor sColor, \
                  CS123SceneColor rColor, float shininess, CS123SceneFileMap texture, float blend):
        CMTM(cum_trans_mat),
        objectType(objectType),
        dColor(dColor),
        aColor(aColor),
        sColor(sColor),
        rColor(rColor),
        shininess(shininess),
        texture(texture),
        blend(blend)
    {
    }
};

class Scene {
public:
    Scene();
    Scene(Scene &scene);
    virtual ~Scene();

    virtual void settingsChanged() {}

    static void parse(Scene *sceneToFill, CS123ISceneParser *parser);

    CS123SceneGlobalData m_global_data;
    CS123SceneCameraData m_camera_data;
    std::vector<PrimitiveData> m_flattenedData;
    std::vector<CS123SceneLightData> m_light_data;

protected:

    // Adds a primitive to the scene.
    virtual void addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix);

    // Adds a light to the scene.
    virtual void addLight(const CS123SceneLightData &sceneLight);

    // Sets the global data for the scene.
    virtual void setGlobal(const CS123SceneGlobalData &global);

    //helper method to recursively traverse the tree
    virtual void traverse(CS123SceneNode *curr_node, glm::mat4 curr_trans);
};


#endif // SCENE_H
