//
// Created by rodrigo on 18/08/24.
//
#include "EntityManager.h"
#ifndef GAMEENGINE_H
#define GAMEENGINE_H



class GameEngine {

    EntityManager m_entityManager;
    size_t m_currentFrame{0};

    public:
    GameEngine();
    void mainLoop();
    void sUserInput();
    void sMovemment();
    void sCollision();
    void sRender();
    void sEnemySpawner();
};



#endif //GAMEENGINE_H
