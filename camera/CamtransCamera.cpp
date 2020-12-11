/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include <Settings.h>

CamtransCamera::CamtransCamera()
{
    // @TODO: [CAMTRANS] Fill this in...
    m_near = 1.f;
    m_far = 30.f;
    m_aspectRatio = 1.f;
    m_eye = glm::vec4(2.f, 2.f, 2.f, 0.f);
    m_up = glm::vec4(0.f, 1.f, 0.f, 0.f);
    orientLook(m_eye, glm::vec4(-1.f, -1.f, -1.f, 0.f), m_up);
}

void CamtransCamera::setAspectRatio(float a)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_aspectRatio = a;
    updateProjectionMatrix();
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_perspectiveTransformation * m_scaleMatrix;
}

glm::mat4x4 CamtransCamera::getViewMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_rotationMatrix * m_translationMatrix;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_scaleMatrix;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_perspectiveTransformation;
}

glm::vec4 CamtransCamera::getPosition() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_eye;
}

glm::vec4 CamtransCamera::getLook() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::normalize(-m_w);
}

glm::vec4 CamtransCamera::getUp() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_up;
}

float CamtransCamera::getAspectRatio() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_aspectRatio;
}

float CamtransCamera::getHeightAngle() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_thetaH;
}

glm::vec4 CamtransCamera::getU() {
    return m_u;
}

glm::vec4 CamtransCamera::getV() {
    return m_v;
}

glm::vec4 CamtransCamera::getW() {
    return m_w;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    // @TODO: [CAMTRANS] Fill this in...
    m_eye = eye;
    m_up = up;
    m_w = glm::normalize(-look);
    m_v = glm::normalize(m_up - glm::dot(m_up, m_w) * m_w);
    m_u = glm::normalize(glm::vec4(glm::cross(m_v.xyz(), m_w.xyz()), 0.f));
    updateViewMatrix();
    updateProjectionMatrix();
}

void CamtransCamera::setHeightAngle(float h) {
    // @TODO: [CAMTRANS] Fill this in...
    m_thetaH = h;
    //m_thetaW = 2 * glm::atan(m_aspectRatio * glm::tan(m_thetaH / 2));
    updateProjectionMatrix();
}

void CamtransCamera::translate(const glm::vec4 &v) {
    // @TODO: [CAMTRANS] Fill this in...
    m_eye += v;
    updateViewMatrix();
}

void CamtransCamera::rotateU(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    glm::mat4 rotate_matrix = glm::mat4();
    rotate_matrix[0][0] = 1;
    rotate_matrix[3][3] = 1;
    rotate_matrix[1][1] = glm::cos(glm::radians(degrees));
    rotate_matrix[1][2] = glm::sin(glm::radians(degrees));
    rotate_matrix[2][1] = -glm::sin(glm::radians(degrees));
    rotate_matrix[2][2] = glm::cos(glm::radians(degrees));
    m_u = rotate_matrix * m_u;
    m_v = rotate_matrix * m_v;
    m_w = rotate_matrix * m_w;
    updateViewMatrix();
}

void CamtransCamera::rotateV(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    glm::mat4 rotate_matrix = glm::mat4();
    rotate_matrix[0][0] = glm::cos(glm::radians(degrees));
    rotate_matrix[3][3] = 1;
    rotate_matrix[1][1] = 1;
    rotate_matrix[0][2] = glm::sin(glm::radians(degrees));
    rotate_matrix[2][0] = -glm::sin(glm::radians(degrees));
    rotate_matrix[2][2] = glm::cos(glm::radians(degrees));
    m_u = rotate_matrix * m_u;
    m_v = rotate_matrix * m_v;
    m_w = rotate_matrix * m_w;
    updateViewMatrix();
}

void CamtransCamera::rotateW(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    glm::mat4 rotate_matrix = glm::mat4();
    rotate_matrix[0][0] = glm::cos(glm::radians(degrees));
    rotate_matrix[3][3] = 1;
    rotate_matrix[2][2] = 1;
    rotate_matrix[0][1] = glm::sin(glm::radians(degrees));
    rotate_matrix[1][0] = -glm::sin(glm::radians(degrees));
    rotate_matrix[1][1] = glm::cos(glm::radians(degrees));
    m_u = rotate_matrix * m_u;
    m_v = rotate_matrix * m_v;
    m_w = rotate_matrix * m_w;
    updateViewMatrix();
}

void CamtransCamera::setClip(float nearPlane, float farPlane) {
    // @TODO: [CAMTRANS] Fill this in...
    m_near = nearPlane;
    m_far = farPlane;
    updateProjectionMatrix();
}

void CamtransCamera::updateProjectionMatrix() {
    // @TODO: [CAMTRANS] Fill this in...
    updateScaleMatrix();
    updatePerspectiveMatrix();
}

void CamtransCamera::updatePerspectiveMatrix() {
    // @TODO: [CAMTRANS] Fill this in...
    float c = -m_near / m_far;
    m_perspectiveTransformation = glm::transpose(glm::mat4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1/(c+1), c/(c+1), 0, 0, -1, 0});
    //m_perspectiveTransformation = glm::transpose(m_perspectiveTransformation);
}

void CamtransCamera::updateScaleMatrix() {
    // @TODO: [CAMTRANS] Fill this in...
    float a = 1 / (m_aspectRatio * glm::tan(glm::radians(m_thetaH) / 2) * m_far);
    float b = 1 / (glm::tan(glm::radians(m_thetaH) / 2) * m_far);
    float c = 1 / m_far;

    m_scaleMatrix = glm::transpose(glm::mat4{a, 0, 0, 0, 0, b, 0, 0, 0, 0, c, 0, 0, 0, 0, 1});
}

void CamtransCamera::updateViewMatrix() {
    // @TODO: [CAMTRANS] Fill this in...
    updateRotationMatrix();
    updateTranslationMatrix();
}

void CamtransCamera::updateTranslationMatrix() {
    // @TODO: [CAMTRANS] Fill this in...
    m_translationMatrix = glm::transpose(glm::mat4{1, 0, 0, -m_eye.x, 0, 1, 0, -m_eye.y, 0, 0, 1, -m_eye.z, 0, 0, 0, 1});
}

void CamtransCamera::updateRotationMatrix() {
    // @TODO: [CAMTRANS] Fill this in...
    m_rotationMatrix = glm::transpose(glm::mat4{m_u.x, m_u.y, m_u.z, 0, m_v.x, m_v.y, m_v.z, 0, m_w.x, m_w.y, m_w.z, 0, 0, 0, 0, 1});
}
