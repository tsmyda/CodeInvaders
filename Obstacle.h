//
// Created by tomek on 25.05.24.
//
#pragma once
#ifndef SPACEINVADERS_OBSTACLE_H
#define SPACEINVADERS_OBSTACLE_H

#include "vector"
#include "Block.h"

class Obstacle {
public:
    Obstacle(Vector2 position);
    void Draw();
    Vector2 position;
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;
};


#endif //SPACEINVADERS_OBSTACLE_H
