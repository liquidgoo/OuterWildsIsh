#include "SFML/Graphics.hpp"
#include "Body.h"

#pragma once

class Contact {
public:
    Body* bodies[2];
    sf::Vector2f contactPoint;
    sf::Vector2f contactNormal;
    float penetration;
};

