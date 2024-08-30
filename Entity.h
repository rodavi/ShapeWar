//
// Created by rodrigo on 18/08/24.
//
#include <memory>
#include <string>
#include "components.h"

#ifndef ENTITY_H
#define ENTITY_H



class Entity {
    friend class EntityManager;
    const size_t m_id{0};
    const std::string m_tag{"Default"};
    bool m_alive{true};
    Entity(const std::string& tag, const size_t id):
    m_id(id), m_tag(tag){}

    public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CShape> cShape;
    //std::shared_ptr<CBBox> cBBox;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CLifespan> cLifespan;
    std::shared_ptr<CScore> cScore;

    const std::string& tag(){return m_tag;}
    bool alive() {
        return m_alive;
    }
    void destroy(){m_alive = false;}
    const size_t id(){return m_id;}
};



#endif //ENTITY_H
