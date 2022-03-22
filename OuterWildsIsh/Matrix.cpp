#include "Matrix.h"


Matrix Matrix::transpose() {
    return Matrix(sf::Vector2f(row1.x, row2.x), sf::Vector2f(row1.y, row2.y));
}

sf::Vector2f Matrix::operator*(sf::Vector2f& vector) {
    return sf::Vector2f(math::dotProduct(row1, vector), math::dotProduct(row2, vector));
}

Matrix::Matrix(sf::Vector2f row1, sf::Vector2f row2) :
    row1(row1), row2(row2) {}

Matrix::Matrix(void) {}