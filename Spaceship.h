//
// Created by tomek on 25.05.24.
//
#pragma once

#ifndef SPACEINVADERS_SPACESHIP_H
#define SPACEINVADERS_SPACESHIP_H

#include "raylib.h"
#include "Laser.h"
#include "vector"

class Spaceship {
public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    std::vector<Laser> lasers;
    Rectangle getRectangle();
    void Reset();
private:
    Texture2D image;
    Vector2 position;
    double lastFireTime;
};

#endif //SPACEINVADERS_SPACESHIP_H
