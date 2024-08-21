//
// Created by rodrigo on 18/08/24.
//
#include <memory>
#include <string>


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
    std::shared_ptr<CName> cName;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CBBox> cBBox;

    const std::string& tag(){return m_tag;}
    bool alive();
    void destroy(){m_alive = false;}
};



#endif //ENTITY_H
