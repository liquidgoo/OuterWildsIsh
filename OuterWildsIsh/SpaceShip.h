#include "Body.h"


#pragma once

class SpaceShip
{
    Body* body;

    const float thrustForce = 1500;
    const float strafeForce = 1000;
    const float rotateForce = 15000;
    const float directRotation = 10000;

public:
    bool forward;
    bool backward;
    bool strafeL;
    bool strafeR;
    bool rotL;
    bool rotR;
    bool stabilize;

    void dirRotL(void);
    void dirRotR(void);

    void doControl(float time);



    sf::Vector2f getPosition(void);


    SpaceShip(Body* body);
};

