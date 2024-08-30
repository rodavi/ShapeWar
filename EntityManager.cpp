//
// Created by rodrigo on 18/08/24.
//

#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(){}

void EntityManager::update() {
    for(auto e:m_toAdd) {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    m_toAdd.clear();

    removeDeadEntities(m_entities);
    removeDeadEntities(m_entityMap["bullet"]);
    removeDeadEntities(m_entityMap["enemy"]);
    removeDeadEntities(m_entityMap["smallEnemies"]);

}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag){

    // Create a new Entity object
    //auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    // store it in the vector of all entities
    m_toAdd.push_back(e);
    // [version changed] store it in the map of the tag->entity vector
    // m_entityMap[tag].push_back(e);
    // return the shared pointer pointing to that entity
    return e;
}

void EntityManager::removeDeadEntities(EntityVec& vec) {
    vec.erase(
        std::remove_if(vec.begin(), vec.end(),
            [](std::shared_ptr<Entity> e){return !e->alive();}),
            vec.end());
}

EntityVec& EntityManager::getEntities() {
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag) {
    return m_entityMap[tag];
}
