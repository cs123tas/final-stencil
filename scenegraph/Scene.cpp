#include "Scene.h"
#include "camera/Camera.h"

#include "glm/gtx/transform.hpp"


Scene::Scene()
{
}

Scene::Scene(Scene &scene)
{
    // We need to set the global constants to one when we duplicate a scene,
    // otherwise the global constants will be double counted (squared)
    CS123SceneGlobalData global = { 1, 1, 1, 1};
    setGlobal(global);

    // TODO [INTERSECT]
    // Make sure to copy over the lights and the scenegraph from the old scene,
    // as well as any other member variables your new scene will need.
    m_flattenedData = scene.m_flattenedData;
    m_global_data = scene.m_global_data;
    m_camera_data = scene.m_camera_data;
    m_light_data = scene.m_light_data;
}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D
    m_flattenedData.clear();
}


void Scene::addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix) {
    m_flattenedData.push_back(PrimitiveData(matrix, scenePrimitive.type, scenePrimitive.material.cDiffuse,\
                                            scenePrimitive.material.cAmbient, scenePrimitive.material.cSpecular, \
                                            scenePrimitive.material.cReflective, scenePrimitive.material.shininess, \
                                            scenePrimitive.material.textureMap, scenePrimitive.material.blend));
}

void Scene::addLight(const CS123SceneLightData &sceneLight) {
    m_light_data.push_back(sceneLight);
}

void Scene::setGlobal(const CS123SceneGlobalData &global) {
    m_global_data = global;
}

void Scene::traverse(CS123SceneNode *curr_node, glm::mat4 curr_trans) {
    //alter the current transformation with current data
    glm::mat4 trans_changes = glm::mat4();
    for (unsigned long i = 0; i < curr_node->transformations.size(); i++) {
        switch(curr_node->transformations[i]->type) {
        case TRANSFORMATION_SCALE:
            trans_changes = trans_changes * glm::scale(curr_node->transformations[i]->scale);
            break;
        case TRANSFORMATION_ROTATE:
            trans_changes = trans_changes * glm::rotate(curr_node->transformations[i]->angle, \
                                                        curr_node->transformations[i]->rotate);
            break;
        case TRANSFORMATION_TRANSLATE:
            trans_changes = trans_changes * glm::translate(curr_node->transformations[i]->translate);
            break;
        case TRANSFORMATION_MATRIX:
            trans_changes = trans_changes * curr_node->transformations[i]->matrix;
            break;
        }
    }

    //apply transformation changes from this block to curr_trans
    curr_trans = curr_trans * trans_changes;

    //store info from the node here
    for (unsigned long i = 0; i < curr_node->primitives.size(); i++) {
        addPrimitive(*curr_node->primitives[i], curr_trans);
    }

    //recursively call traverse on all children
    for (unsigned long i = 0; i < curr_node->children.size(); i++) {
        traverse(curr_node->children[i], curr_trans);
    }
}

