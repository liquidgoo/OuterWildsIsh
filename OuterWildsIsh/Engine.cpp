#include "Engine.h"

float Engine::getGravity(Body* body1, Body* body2) {
    return (body1->getMass() * body2->getMass()) / std::pow(math::abs(body2->getPosition() - body1->getPosition()), 2);
}

void Engine::updateGravity(float time) {
    for (int i = 0; i < bodies.size() - 1; i++) {
        for (int j = i + 1; j < bodies.size(); j++) {
            force = getGravity(bodies[i], bodies[j]) *
                math::normalize(bodies[j]->getPosition() - bodies[i]->getPosition());
            bodies[i]->adjustVelocities(force, time);
            bodies[j]->adjustVelocities(-force, time);
        }
    }
}

void Engine::updatePositions(float time) {
    for (Body* body : bodies) {
        body->updatePosition(time);
    }
    collisionTester->updatePositions();
}

void Engine::simulateNextFrame(float time) {
    updateGravity(time);
    updatePositions(time);
    collisionTester->findCollisions();
    collisionResolver->resolveCollisions();
}

void Engine::appendBody(sf::CircleShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity,
    float mass, float restitution) {
    bodies.push_back(new Body(shape, position, velocity, angularVelocity, mass, restitution));
    collisionTester->appendAABB(shape->getGlobalBounds(), bodies.size() - 1);
}

void Engine::appendBody(sf::ConvexShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity,
    float mass, float restitution) {
    bodies.push_back(new Body(shape, position, velocity, angularVelocity, mass, restitution));
    collisionTester->appendAABB(shape->getGlobalBounds(), bodies.size() - 1);
}

Body* Engine::getFirst(void) {
    return bodies[0];
}
Engine::Engine(void) {
    bodies = std::vector<Body*>();
    contacts = std::vector<Contact*>();
    collisionTester = new CollisionTester(bodies, contacts);
    collisionResolver = new CollisionResolver(contacts);
}