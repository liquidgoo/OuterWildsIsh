#include "SFML/Graphics.hpp"
#pragma once
namespace math
{
    const float PI = 3.14159265359;
    float abs(sf::Vector2f vector);
    sf::Vector2f normalize(sf::Vector2f vector);
    float sqr(sf::Vector2f vector);
    float getAxis(sf::Vector2f vector, int axis);
    float dotProduct(sf::Vector2f a, sf::Vector2f b);
    float distance(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    sf::Vector2f rotate(sf::Vector2f vector, float angle);
    sf::Vector2f perpendicular(sf::Vector2f vector);
}