//
// Created by auguste on 31/05/22.
//

#include "../include/Camera.h"

//Private methods



//Public methods
Camera::Camera() {
    this->x = 0.0f;
    this->y = 0.0f;
}


Camera::~Camera() {

}


float Camera::getX() {
    return this->x;
}


float Camera::getY() {
    return this->y;
}


void Camera::addPosX(float x) {
    this->x += x;
}


void Camera::addPosY(float y) {
    this->y += y;
}


void Camera::setPos(float x, float y) {
    this->x = x;
    this->y = y;
}