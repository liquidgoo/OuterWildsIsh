#include "SFML/Graphics.hpp"
#include "math.h"

#pragma once
class Matrix
{
public:
    sf::Vector2f row1, row2;
    Matrix transpose();

    sf::Vector2f operator*(sf::Vector2f& vector);

    Matrix(sf::Vector2f row1, sf::Vector2f row2);
    Matrix(void);
};
