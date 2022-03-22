#include "Body.h"

void Body::setOrigin(sf::CircleShape* shape) {
    shape->setOrigin(shape->getRadius(), shape->getRadius());
}

void Body::setOrigin(sf::ConvexShape* shape) {
    sf::Vector2f origin(0, 0);
    for (int i = 0; i < shape->getPointCount(); i++) {
        origin += shape->getPoint(i);
    }
    origin.x /= shape->getPointCount();
    origin.y /= shape->getPointCount();
    shape->setOrigin(origin);
}

void Body::setMomentOfInertia(sf::CircleShape* shape) {
    momentOfInertia = mass * std::pow(shape->getRadius(), 2) / 2;
}

void Body::setMomentOfInertia(sf::ConvexShape* shape) {
    radius = 0;
    for (int i = 0; i < shape->getPointCount(); i++) {
        radius += std::sqrt(std::pow(shape->getPoint(i).x - shape->getOrigin().x, 2) +
            std::pow(shape->getPoint(i).y - shape->getOrigin().y, 2));
    }
    radius /= shape->getPointCount();
    momentOfInertia = mass * radius * radius / 2;
}

int Body::getSupportPoints(sf::Vector2f direction, sf::Vector2f* points) {
    if (shapeType == eShapeType::CIRCLE) {
        points[0] = shape->getPosition() + math::normalize(direction) * radius;
        return 1;
    }
    if (shapeType == eShapeType::CONVEX) {
        int count = 0;
        const float threshold = 1.0E-2;
        float d = math::dotProduct(getPoint(0), direction), maxd = d;
        for (int i = 1; i < shape->getPointCount(); i++) {
            d = math::dotProduct(getPoint(i), direction);
            if (d > maxd) {
                maxd = d;
            }
        }


        for (int i = 0; i < shape->getPointCount(); i++) {
            if (math::dotProduct(getPoint(i), direction) >= maxd - threshold) {
                points[count] = getPoint(i);
                count++;
                if (count == 2) return count;
            }
        }
        return count;
    }
}

sf::Vector2f Body::getPoint(int i) {
    return math::rotate(shape->getPoint(i) - shape->getOrigin(), shape->getRotation()) + shape->getPosition();
}

sf::Vector2f Body::getPosition(void) {
    return shape->getPosition();
}

sf::Vector2f Body::getVelocity(void) {
    return velocity;
}

float Body::getRotation(void) {
    return shape->getRotation();
}

float Body::getAngularVelocity(void) {
    return angularVelocity;
}

float Body::getMass(void) {
    return mass;
}

float Body::getMomentOfInertia(void) {
    return momentOfInertia;
}

float Body::getRadius(void) {
    return radius;
}

float Body::getRestitution(void) {
    return restitution;
}

void Body::adjustVelocities(sf::Vector2f force, float time) {
    velocity += force * time / mass;
}

void Body::updateAngularVelocity(float torque, float time) {
    angularVelocity += torque * time / momentOfInertia;
}

void Body::addAngularVelocity(float delta) {
    angularVelocity += delta / momentOfInertia;
}

void Body::applyImpulse(sf::Vector2f impulse, sf::Vector2f relativeContactPoint) {
    velocity += impulse / mass;
    angularVelocity += (impulse.y * relativeContactPoint.x - impulse.x * relativeContactPoint.y) / momentOfInertia;
}

void Body::updatePosition(float time) {
    shape->move(velocity.x * time, velocity.y * time);
    shape->rotate(angularVelocity / math::PI * 180 * time);
}

void Body::move(sf::Vector2f linearMove) {
    shape->move(linearMove);
}

void Body::rotate(float rotation) {
    shape->rotate(rotation / math::PI * 180);
}

sf::Shape* Body::getShape(void) {
    return shape;
}

eShapeType Body::getShapeType(void) {
    return shapeType;
}

sf::FloatRect Body::getBoundRect(void) {
    return shape->getGlobalBounds();
}

Body::Body(sf::CircleShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity, float mass,
    float restitution) :
    shape(shape), velocity(velocity), angularVelocity(angularVelocity), mass(mass), radius(shape->getRadius()),
    restitution(restitution) {
    shapeType = eShapeType::CIRCLE;
    setOrigin(shape);
    shape->setPosition(position);
    setMomentOfInertia(shape);
}

Body::Body(sf::ConvexShape* shape, sf::Vector2f position, sf::Vector2f velocity, float angularVelocity, float mass,
    float restitution) :
    shape(shape), velocity(velocity), angularVelocity(angularVelocity), mass(mass), restitution(restitution) {
    shapeType = eShapeType::CONVEX;
    setOrigin(shape);
    shape->setPosition(position);
    setMomentOfInertia(shape);
}


