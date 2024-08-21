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
    // if e is dead, remove it from m_entities
    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
            [](Entity* e){return !e->alive();}),
            m_entities.end());
    // if e is dead, remove it from m_entityMap[e->tag()]
    m_entityMap.erase(
        std::remove_if(m_entityMap.begin(), m_entityMap.end(),
            [](Entity* e){return !e->alive();}),
            m_entityMap.end());

    m_toAdd.clear();
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

EntityVec& EntityManager::getEntities() {
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag) {
    return m_entityMap[tag];
}
