//
// Created by tomek on 25.05.24.
//

#include "Block.h"

Block::Block(Vector2 position) {
    this->position = position;
}

void Block::Draw() {
    DrawRectangle(position.x, position.y, 3, 3, BLUE);
}

Rectangle Block::getRectangle() {
    return {position.x, position.y, 3, 3};
}
