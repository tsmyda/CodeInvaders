//
// Created by tomek on 25.05.24.
//
#pragma once
#include "Spaceship.h"
#include "Obstacle.h"
#include "Alien.h"
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H
#include "string"

class Game {
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

    bool run;
    int lives = 3;
    int score;
    int level;
    std::vector<std::string> levels = {"INTERN", "JUNIOR", "SENIOR"};
private:
    Spaceship spaceship;
    void DeleteInactiveLasers();
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> aliens;
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    int aliensDirection;
    void MoveDownAliens(int distance);
    std::vector<Laser> alienLaser;
    void AlienShootLaser();
    float alienLaserShootInterval = 0.6;
    float timeLastAlienFired;
    void CheckForCollisions();
    void GameOver();
    void NextLevel();
    void Init();
    void Reset();
};


#endif //SPACEINVADERS_GAME_H
