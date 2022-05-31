//
// Created by auguste on 31/05/22.
//

#ifndef EDITEUR_RTB_CAMERA_H
#define EDITEUR_RTB_CAMERA_H


class Camera {
private:
    float x, y;

public:
    Camera();
    ~Camera();

    float getX();
    float getY();
    void addPosX(float x);
    void addPosY(float y);
    void setPos(float x, float y);
};


#endif //EDITEUR_RTB_CAMERA_H
