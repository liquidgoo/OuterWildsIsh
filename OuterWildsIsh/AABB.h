#include "SFML/Graphics.hpp"

#pragma once
class AABB
{
public:
    sf::Vector2f
        min,
        max;
    const int bodyIndex;

    void setPosition(sf::FloatRect rect);

    AABB(sf::FloatRect rect, int bodyIndex);

};