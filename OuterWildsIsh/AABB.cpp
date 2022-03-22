#include "AABB.h"

void AABB::setPosition(sf::FloatRect rect) {
    min.x = rect.left;
    min.y = rect.top;
    max.x = min.x + rect.width;
    max.y = min.y + rect.height;
}

AABB::AABB(sf::FloatRect rect, int bodyIndex) :
    min(rect.left, rect.top), max(min.x + rect.width, min.y + rect.height), bodyIndex(bodyIndex) {}