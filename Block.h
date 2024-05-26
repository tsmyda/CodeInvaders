//
// Created by tomek on 25.05.24.
//
#pragma once
#ifndef SPACEINVADERS_BLOCK_H
#define SPACEINVADERS_BLOCK_H

#include "raylib.h"

class Block {
public:
    Block(Vector2 position);
    void Draw();
    Rectangle getRectangle();
private:
    Vector2 position;
};


#endif //SPACEINVADERS_BLOCK_H
