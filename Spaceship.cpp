//
// Created by tomek on 25.05.24.
//

#include "Spaceship.h"

Spaceship::Spaceship() {
    image = LoadTexture("../graphics/cpp.png");
    position.x = (GetScreenWidth()-image.width)/2;
    position.y = GetScreenHeight()-image.height-120;
    lastFireTime = 0.0;
}

Spaceship::~Spaceship() {
    UnloadTexture(image);
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
    position.x -= 5;
    if (position.x<15) position.x = 15;
}

void Spaceship::MoveRight() {
    position.x += 5;
    if (position.x>GetScreenWidth()-image.width-15) position.x = GetScreenWidth()-image.width-15;
}

void Spaceship::FireLaser() {
    if (GetTime() - lastFireTime >=0.4 && lasers.size()<2) {
        lasers.push_back(Laser({position.x+image.width/2, position.y},-6));
        lastFireTime = GetTime();
    }

}

Rectangle Spaceship::getRectangle() {
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset() {
    position.x = (GetScreenWidth()-image.width)/2.0f;
    position.y = GetScreenHeight() - image.height-80;
    lasers.clear();
}
