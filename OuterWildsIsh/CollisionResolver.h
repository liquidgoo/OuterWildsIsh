#include <vector>
#include "Contact.h"
#include "Matrix.h"

#pragma once
class CollisionResolver
{
private:
    std::vector<Contact*>& contacts;

    Matrix contactBasisTransposed;
    float velocityChangePerUnitImpulse;
    sf::Vector2f relativeContactPosition, closingVelocity, contactImpulse;
    float restitution, deltaVelocity;
    void adjustVelocities(Contact* contact);

    float linearInertia[2], angularInertia[2], totalInertia, linearMove[2], angularMove[2];
    const float ANGULAR_MOVE_LIMIT = 0.2;
    float angularMoveLimit;
    void adjustPositions(Contact* contact);
public:
    void resolveCollisions(void);

    CollisionResolver(std::vector<Contact*>& contacts);
};

