//
// Created by tomek on 25.05.24.
//
#pragma once
#include "raylib.h"

#ifndef SPACEINVADERS_LASER_H
#define SPACEINVADERS_LASER_H


class Laser {
public:
    Laser(Vector2 position, int speed);
    void Update();
    void Draw();
    bool active;
    Rectangle getRectangle();
private:
    Vector2 position;
    int speed;
};


#endif //SPACEINVADERS_LASER_H
