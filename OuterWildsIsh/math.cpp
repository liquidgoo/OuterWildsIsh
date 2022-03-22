#include "math.h"

float math::abs(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f math::normalize(sf::Vector2f vector) {
    return vector / abs(vector);
}

float math::sqr(sf::Vector2f vector) {
    return vector.x * vector.x + vector.y * vector.y;
}

float math::getAxis(sf::Vector2f vector, int axis) {
    if (axis == 0) return vector.x;
    if (axis == 1) return vector.y;
}

float math::dotProduct(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

float cosinus;
float sinus;

float math::distance(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
    return std::abs((a.y - b.y) * c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y) /
        std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

sf::Vector2f math::rotate(sf::Vector2f vector, float angle) {
    angle = angle / 180 * PI;
    sinus = std::sin(angle);
    cosinus = std::cos(angle);
    return sf::Vector2f(cosinus * vector.x - sinus * vector.y, sinus * vector.x + cosinus * vector.y);
}

sf::Vector2f math::perpendicular(sf::Vector2f vector) {
    return sf::Vector2f(-vector.y, vector.x);
}