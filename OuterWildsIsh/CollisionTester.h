#include "AABB.h"
#include "math.h"
#include "Contact.h"

#pragma once

bool cmpAABBs(AABB* a, AABB* b);

class CollisionTester
{
private:
    std::vector<Body*>& bodies;
    std::vector<Contact*>& contacts;
    Contact* newContact;
    float penetration;
    void testCollisionCircleCircle(Body* a, Body* b);

    std::vector<sf::Vector2f> axes;
    float minA, maxA, minB, maxB;
    float minOverlap, overlap, currentProjection;
    sf::Vector2f mtv;
    sf::Vector2f contactA[2], contactB[2];
    int contactCountA, contactCountB;
    void testColissionPolyPoly(Body* a, Body* b);

    sf::Vector2f closestPoint, point, vb;
    float minD, d, t;
    void testCollisionCirclePoly(Body* a, Body* b);

    void testCollisionNarrow(Body* a, Body* b);
    std::vector<AABB*> AABBs;
    sf::Vector2f mean, meanSqrs, variance, AABBCentre;
public:
    void findCollisions(void);
    void updatePositions(void);
    void appendAABB(sf::FloatRect rect, int bodyIndex);
    CollisionTester(std::vector<Body*>& bodies, std::vector<Contact*>& contacts);
};

