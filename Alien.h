//
// Created by tomek on 25.05.24.
//

#ifndef SPACEINVADERS_ALIEN_H
#define SPACEINVADERS_ALIEN_H

#pragma once
#include <raylib.h>

class Alien {
public:
    Alien(int type, Vector2 position);
    void Update(int direction);
    void Draw();
    int GetType();
    static void UnloadImages();
    Rectangle getRectangle();
    static Texture2D alienImages[3];
    int type;
    Vector2 position;
private:
};

#endif //SPACEINVADERS_ALIEN_H
