//
// Created by tomek on 25.05.24.
//

#include "Game.h"


Game::Game() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    lives = 3;
    level=0;
    score = 0;
    alienLaserShootInterval=0.6;
    run = true;
}

Game::~Game() {

}

void Game::Update() {
    if (aliens.empty()) {
        NextLevel();
    }
    if (run) {
        for (auto &laser: spaceship.lasers) {
            laser.Update();
        }
        MoveAliens();
        AlienShootLaser();
        for (auto &laser: alienLaser) {
            laser.Update();
        }
        DeleteInactiveLasers();
        CheckForCollisions();
    } else {
        if(IsKeyDown(KEY_ENTER)) {
            Reset();
            Init();
        }
    }
}

void Game::Draw() {
    spaceship.Draw();
    for (auto& laser: spaceship.lasers) {
        laser.Draw();
    }
    for (auto& obstacle: obstacles) {
        obstacle.Draw();
    }
    for (auto& alien: aliens) {
        alien.Draw();
    }
    for (auto& laser: alienLaser) {
        laser.Draw();
    }
}

void Game::DeleteInactiveLasers() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->active) {
            it = spaceship.lasers.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = alienLaser.begin(); it != alienLaser.end();) {
        if (!it->active) {
            it = alienLaser.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::HandleInput() {
    if (run) {
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser();
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::grid[0].size()*3;
    float gap = (GetScreenWidth()-3*obstacleWidth)/4;
    for (int i=0; i<3; i++) {
        float offsetX = (i+1)*gap + i*obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight()-250)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens() {
    std::vector<Alien> aliens;
    for (int i=0; i<3; i++) {
        for (int j=0; j<10; j++) {
            float x = 75 + j*65;
            float y = 100 + i*65;
            aliens.push_back(Alien(i+1, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for(auto& alien: aliens) {
        if (alien.position.x+alien.alienImages[alien.type-1].width > GetScreenWidth() - 15) {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x<15) {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance) {
    for (auto& alien: aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser() {
//    double currTime = GetTime();
    if (GetTime() - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size()-1);
        Alien& alien = aliens[randomIndex];
        alienLaser.push_back(Laser({alien.position.x+alien.alienImages[alien.type-1].width/2,
                                    alien.position.y+alien.alienImages[alien.type-1].height}, 6));
        timeLastAlienFired = GetTime();
    }

}

void Game::CheckForCollisions() {
    //Spaceship lasers
    for (auto& laser: spaceship.lasers) {
        auto it = aliens.begin();
        while(it!=aliens.end()) {
            if (CheckCollisionRecs(it -> getRectangle(), laser.getRectangle())) {
                int type = it->type;
                switch (type) {
                    case 1: score+=200;
                    case 2: score+=150;
                    case 3: score+=100;
                }
                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it!=obstacle.blocks.end()) {
                if (CheckCollisionRecs(it ->getRectangle(), laser.getRectangle())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }
    //Alien lasers
    for (auto& laser: alienLaser) {
        if (CheckCollisionRecs(laser.getRectangle(), spaceship.getRectangle())) {
            laser.active = false;
            lives--;
            if (lives==0) {
                GameOver();
            }

        }
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it!=obstacle.blocks.end()) {
                if (CheckCollisionRecs(it ->getRectangle(), laser.getRectangle())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }
    //Alien collision
    for (auto& alien : aliens) {
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it!=obstacle.blocks.end()) {
               if (CheckCollisionRecs(it->getRectangle(), alien.getRectangle())) {
                   it = obstacle.blocks.erase(it);
               } else {
                   ++it;
               }
            }
        }
        if (CheckCollisionRecs(alien.getRectangle(), spaceship.getRectangle())) {
            //
        }
    }
}

void Game::GameOver() {
    run = false;
}

void Game::Init() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    lives = 3;
    level=0;
    score = 0;
    alienLaserShootInterval=0.6;
    run = true;
}

void Game::Reset() {
    spaceship.Reset();
    aliens.clear();
    alienLaser.clear();
    obstacles.clear();
}
void Game::NextLevel() {
    spaceship.Reset();
    alienLaser.clear();
    obstacles.clear();
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    level+=1;
    alienLaserShootInterval-=0.15;

}
