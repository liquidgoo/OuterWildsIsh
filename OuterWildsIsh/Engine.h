#include "SFML/Graphics.hpp"
#include "CollisionTester.h"
#include "CollisionResolver.h"

#pragma once
class Engine
{
private:
    std::vector<Body *> bodies;
    CollisionTester *collisionTester;
    std::vector<Contact*> contacts;
    CollisionResolver* collisionResolver;

    float getGravity(Body *body1, Body *body2);
    sf::Vector2f force;
    void updateGravity(float time);
    void updatePositions(float time);

public:
    void simulateNextFrame(float time);
    void appendBody(sf::CircleShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity, float mass, float restitution);
    void appendBody(sf::ConvexShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity, float mass, float restitution);
    Body* getFirst(void);
    Engine(void);
};