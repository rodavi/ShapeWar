//
// Created by rodrigo on 18/08/24.
//

#include "GameEngine.h"
#include "EntityManager.h"

void GameEngine::mainLoop() {
    m_entityManager.update();
    /*sUserInput();
    sMovemment();
    sCollision();
    sRender();*/
    m_currentFrame++;
}

void GameEngine::sEnemySpawner() {
    auto e = m_entityManager.addEntity("Enemy");

}