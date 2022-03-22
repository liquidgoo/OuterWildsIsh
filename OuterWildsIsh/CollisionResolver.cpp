#include "CollisionResolver.h"


void CollisionResolver::adjustVelocities(Contact* contact) {
    contactBasisTransposed.row1 = contact->contactNormal;
    contactBasisTransposed.row2 = math::perpendicular(contact->contactNormal);

    velocityChangePerUnitImpulse = (1 / contact->bodies[0]->getMass()) + (1 / contact->bodies[1]->getMass());

    relativeContactPosition = contact->contactPoint - contact->bodies[0]->getPosition();
    velocityChangePerUnitImpulse += (relativeContactPosition.y * relativeContactPosition.y * contact->contactNormal.x *
        contact->contactNormal.x +
        relativeContactPosition.x * relativeContactPosition.x * contact->contactNormal.y *
        contact->contactNormal.y -
        2 * relativeContactPosition.x * relativeContactPosition.y *
        contact->contactNormal.x * contact->contactNormal.y) /
        contact->bodies[0]->getMomentOfInertia();
    closingVelocity = contact->bodies[0]->getAngularVelocity() * math::perpendicular(relativeContactPosition) +
        contact->bodies[0]->getVelocity();

    relativeContactPosition = contact->contactPoint - contact->bodies[1]->getPosition();
    velocityChangePerUnitImpulse += (relativeContactPosition.y * relativeContactPosition.y * contact->contactNormal.x *
        contact->contactNormal.x +
        relativeContactPosition.x * relativeContactPosition.x * contact->contactNormal.y *
        contact->contactNormal.y -
        2 * relativeContactPosition.x * relativeContactPosition.y *
        contact->contactNormal.x * contact->contactNormal.y) /
        contact->bodies[1]->getMomentOfInertia();
    closingVelocity -= contact->bodies[1]->getAngularVelocity() * math::perpendicular(relativeContactPosition) +
        contact->bodies[1]->getVelocity();

    closingVelocity = contactBasisTransposed * closingVelocity;

    restitution = (contact->bodies[0]->getRestitution() + contact->bodies[1]->getRestitution()) / 2.0f;

    deltaVelocity = -closingVelocity.x * (1 + restitution);
    contactImpulse.x = deltaVelocity / velocityChangePerUnitImpulse;
    contactImpulse.y = 0;

    contactImpulse = contactBasisTransposed.transpose() * contactImpulse;

    contact->bodies[0]->applyImpulse(contactImpulse, contact->contactPoint - contact->bodies[0]->getPosition());
    contact->bodies[1]->applyImpulse(-contactImpulse, contact->contactPoint - contact->bodies[1]->getPosition());
}

void CollisionResolver::adjustPositions(Contact* contact) {
    totalInertia = 0;
    for (int i = 0; i < 2; i++) {
        linearInertia[i] = 1 / contact->bodies[i]->getMass();
        totalInertia += linearInertia[i];


        relativeContactPosition = contact->contactPoint - contact->bodies[i]->getPosition();
        angularInertia[i] = (relativeContactPosition.y * relativeContactPosition.y * contact->contactNormal.x *
            contact->contactNormal.x +
            relativeContactPosition.x * relativeContactPosition.x * contact->contactNormal.y *
            contact->contactNormal.y -
            2 * relativeContactPosition.x * relativeContactPosition.y * contact->contactNormal.x *
            contact->contactNormal.y) / contact->bodies[i]->getMomentOfInertia();
        totalInertia += angularInertia[i];

    }

    linearMove[0] = -contact->penetration * linearInertia[0] / totalInertia;
    linearMove[1] = contact->penetration * linearInertia[1] / totalInertia;
    angularMove[0] = contact->penetration * angularInertia[0] / totalInertia;
    angularMove[1] = -contact->penetration * angularInertia[1] / totalInertia;

    for (int i = 0; i < 2; i++) {
        angularMoveLimit = ANGULAR_MOVE_LIMIT * math::abs(contact->contactPoint - contact->bodies[i]->getPosition());
        if (std::abs(angularMove[i]) > angularMoveLimit) {
            linearMove[i] += angularMove[i];
            if (angularMove[i] > 0) angularMove[i] = angularMoveLimit;
            if (angularMove[i] < 0) angularMove[i] = -angularMoveLimit;
            linearMove[i] -= angularMove[i];
        }
    }
    for (int i = 0; i < 2; i++) {
        contact->bodies[i]->move(contact->contactNormal * linearMove[i]);
        relativeContactPosition = contact->contactPoint - contact->bodies[i]->getPosition();
        if (angularInertia[i] != 0.0f) {
            contact->bodies[i]->rotate(((relativeContactPosition.x * contact->contactNormal.y -
                relativeContactPosition.y * contact->contactNormal.x) /
                contact->bodies[i]->getMomentOfInertia() * angularInertia[i] * angularMove[i]));
        }
    }
}

void CollisionResolver::resolveCollisions(void) {
    while (contacts.size() > 0) {
        adjustPositions(contacts[0]);
        adjustVelocities(contacts[0]);
        delete (contacts[0]);
        contacts.erase(contacts.begin());
    }
}

CollisionResolver::CollisionResolver(std::vector<Contact*>& contacts) :
    contacts(contacts), contactBasisTransposed(Matrix()) {}