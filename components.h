//
// Created by rodrigo on 19/08/24.
//

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vec2.h"

#ifndef COMPONENTS_H
#define COMPONENTS_H

class CTransform {
    public:
    Vec2 position{0.0,0.0};
    Vec2 velocity{0.0, 0.0};
    float angle{0};
    CTransform(const Vec2& p, const Vec2& v, float a)
        : position{p}, velocity{v}, angle{a}{}
};

/*class CScore {
    int score{0};
    public:
    sf::String text_o;

    CScore(int t, std::string font, const sf::Color& fill, float t_size)
    :score{t} {
        sf::Font o_font;
        if(!o_font.loadFromFile(font)) {
            std::cerr << "Failed to load font" << std::endl;
        }
        else text_o.SetFont(sf::Font::GetDefaultFont());
        //text.setCharacterSize(t_size);
        //text.setFillColor(fill);
        //text.setString(std::to_string(score));
        text_o.SetText(t);
        text_o.SetFont(o_font);
        text_o.SetSize(t_size);
    }
};*/

class CShape {
public:
    sf::CircleShape circle;

    CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
        :circle(radius, points) {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollision {
    public:
    float radius{0};
    CCollision(float r):
    radius{r}{}
};

class CScore {
public:
    int score{0};
    CScore(int s):
    score{s}{}
};

class CLifespan {
    public:
    int remaining{0};
    int total{0};
    CLifespan(int t):
    remaining(t), total(t){}
};

class CInput {
    public:
    bool up{false};
    bool down{false};
    bool left{false};
    bool right{false};
    bool shoot{false};

    CInput(){}
};

#endif //COMPONENTS_H
