#include "SpaceShip.h"


void SpaceShip::doControl(float time) {
    if (forward) body->adjustVelocities(math::rotate(sf::Vector2f(thrustForce, 0), body->getRotation()), time);
    if (backward) body->adjustVelocities(math::rotate(sf::Vector2f(-thrustForce, 0), body->getRotation()), time);
    if (strafeL) body->adjustVelocities(math::rotate(sf::Vector2f(0, -strafeForce), body->getRotation()), time);
    if (strafeR) body->adjustVelocities(math::rotate(sf::Vector2f(0, strafeForce), body->getRotation()), time);
    if (rotL) body->updateAngularVelocity(-rotateForce, time);
    if (rotR) body->updateAngularVelocity(rotateForce, time);
    if (stabilize) {
        body->adjustVelocities(math::normalize(-body->getVelocity()) * thrustForce, time);
        body->updateAngularVelocity((body->getAngularVelocity() < 0 ? 1 : -1) * rotateForce, time);
    }
}

sf::Vector2f SpaceShip::getPosition(void) {
    return body->getPosition();
}

void SpaceShip::dirRotL(void) {
    body->addAngularVelocity(-directRotation);
}
void SpaceShip::dirRotR(void) {
    body->addAngularVelocity(directRotation);
}

SpaceShip::SpaceShip(Body* body) : body(body), forward(false), backward(false),
strafeL(false), strafeR(false), rotL(false), rotR(false) {}