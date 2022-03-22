#include "SFML/Graphics.hpp"
#include "math.h"

#pragma once
enum class eShapeType
{
    CIRCLE,
    CONVEX
};

class Body
{
private:
    sf::Shape* shape;
    eShapeType shapeType;

    sf::Vector2f velocity;
    float angularVelocity;

    float mass, momentOfInertia, radius, restitution;

    void setOrigin(sf::CircleShape* shape);

    void setOrigin(sf::ConvexShape *shape);
    void setMomentOfInertia(sf::CircleShape *shape);
    
    void setMomentOfInertia(sf::ConvexShape* shape);
    sf::Vector2f supportingPoint;
    float dotProd, tempDotProd;

public: 
    int getSupportPoints(sf::Vector2f direction, sf::Vector2f *points);
    
    sf::Vector2f getPoint(int i);

    sf::Vector2f getPosition(void);

    sf::Vector2f getVelocity(void);

    float getRotation(void);

    float getAngularVelocity(void);

    float getMass(void);

    float getMomentOfInertia(void);

    float getRadius(void);
    
    float getRestitution(void);

    void adjustVelocities(sf::Vector2f force, float time);

    void updateAngularVelocity(float torque, float time);

    void addAngularVelocity(float delta);

    void applyImpulse(sf::Vector2f impulse, sf::Vector2f relativeContactPoint);

    void updatePosition(float time);

    void move(sf::Vector2f linearMove);

    void rotate(float rotation);

    sf::Shape* getShape(void);

    eShapeType getShapeType(void);

    sf::FloatRect getBoundRect(void);

    Body(sf::CircleShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity, float mass, float restitution);

    Body(sf::ConvexShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity, float mass, float restitution);

};

