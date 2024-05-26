//
// Created by tomek on 25.05.24.
//

#include <iostream>
#include "Laser.h"

Laser::Laser(Vector2 position, int speed){
    this->position = position;
    this->speed = speed;
    active = true;
}

void Laser::Draw() {
    if (active)
        DrawRectangle(position.x, position.y, 4, 10, WHITE);
}

void Laser::Update() {
    position.y += speed;
    if (active && (position.y>GetScreenHeight()-120 || position.y<20)) {
        active = false;
    }
}

Rectangle Laser::getRectangle() {
    return {position.x, position.y, 4, 10};
}
