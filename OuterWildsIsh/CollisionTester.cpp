#include "CollisionTester.h"

int sortAxis;

bool cmpAABBs(AABB* a, AABB* b) {
    return math::getAxis(a->min, sortAxis) > math::getAxis(b->min, sortAxis);
}

void CollisionTester::testCollisionCircleCircle(Body* a, Body* b) {
    penetration = a->getRadius() + b->getRadius() - math::abs(b->getPosition() - a->getPosition());
    if (penetration < 0.0f) return;
        newContact = new Contact();
        newContact->bodies[0] = a;
        newContact->bodies[1] = b;
        newContact->contactNormal = math::normalize(b->getPosition() - a->getPosition());
        newContact->contactPoint = (a->getPosition() + newContact->contactNormal * a->getRadius()
            + b->getPosition() - newContact->contactNormal * b->getRadius()) / 2.0f;
        newContact->penetration = penetration;
        contacts.push_back(newContact);
    
}

void CollisionTester::testColissionPolyPoly(Body* a, Body* b) {
    axes.clear();
    for (int i = 0; i < a->getShape()->getPointCount(); i++) {
        axes.push_back(math::perpendicular(math::normalize(
            a->getPoint(i) - a->getPoint(i + 1 == a->getShape()->getPointCount() ? 0 : i + 1))));
    }
    for (int i = 0; i < b->getShape()->getPointCount(); i++) {
        axes.push_back(-math::perpendicular(math::normalize(
            b->getPoint(i) - b->getPoint(i + 1 == b->getShape()->getPointCount() ? 0 : i + 1))));
    }
    minOverlap = -1.0f;
    for (int i = 0; i < axes.size(); i++) {
        maxA = minA = math::dotProduct(a->getPoint(0), axes[i]);
        for (int j = 1; j < a->getShape()->getPointCount(); j++) {
            currentProjection = math::dotProduct(a->getPoint(j), axes[i]);
            if (currentProjection < minA) minA = currentProjection;
            if (currentProjection > maxA) maxA = currentProjection;
        }

        maxB = minB = math::dotProduct(b->getPoint(0), axes[i]);
        for (int j = 1; j < b->getShape()->getPointCount(); j++) {
            currentProjection = math::dotProduct(b->getPoint(j), axes[i]);
            if (currentProjection < minB) minB = currentProjection;
            if (currentProjection > maxB) maxB = currentProjection;
        }
        overlap = std::min(maxA, maxB) - std::max(minA, minB);
        if (overlap < 0) return;
        if (minOverlap == -1.0f || overlap < minOverlap) {
            minOverlap = overlap;
            mtv = axes[i];
            if (maxA > maxB) mtv = -mtv;
        }
    }
    newContact = new Contact();
    newContact->bodies[0] = a;
    newContact->bodies[1] = b;
    contactCountA = a->getSupportPoints(mtv, contactA);
    contactCountB = b->getSupportPoints(-mtv, contactB);
    if (contactCountA == 1 && contactCountB == 1) {
        newContact->contactPoint = (contactA[0] + contactB[0]) / 2.0f;
        newContact->contactNormal = math::normalize(contactB[0] - contactA[0]);
        newContact->penetration = math::abs(contactA[0] - contactB[0]);
    }
    if (contactCountA == 2 && contactCountB == 1) {
        newContact->contactPoint = contactB[0];
        newContact->contactNormal = mtv;
        newContact->penetration = math::distance(contactA[0], contactA[1], contactB[0]);
    }
    if (contactCountA == 1 && contactCountB == 2) {
        newContact->contactPoint = contactA[0];
        newContact->contactNormal = mtv;
        newContact->penetration = math::distance(contactB[0], contactB[1], contactA[0]);
    }
    if (contactCountA == 2 && contactCountB == 2) {
        newContact->penetration = math::distance(contactB[0], contactB[1], contactA[0]);
        vb = math::normalize(contactB[1] - contactB[0]);
        sf::Vector2f sum;
        float a1 = math::dotProduct(contactA[0], vb), a2 = math::dotProduct(contactA[1], vb)
            , b1 = math::dotProduct(contactB[0], vb), b2 = math::dotProduct(contactB[1], vb);
        if (a1 > b2 && a2 > b2) {
            sum = contactB[1] + (a2 < a1 ? contactA[1] : contactA[0]);
        }
        else if (a1 < b1 && a2 < b2) {
            sum = contactB[0] + (a2 > a1 ? contactA[1] : contactA[0]);
        }
        else {
            if (a1 > b2 || a2 > b2) {
                sum = contactB[1] - mtv * newContact->penetration;
            }
            else {
                sum = (a2 > a1 ? contactA[1] : contactA[0]) + mtv * newContact->penetration;
            }
            if (a1 < b1 || a2 < b1) {
                sum += contactB[0] - mtv * newContact->penetration;
            }
            else {
                sum += (a2 < a1 ? contactA[1] : contactA[0]) + mtv * newContact->penetration;
            }
        }


        newContact->contactPoint = sum / 2.0f;

        newContact->contactNormal = mtv;
    }
    contacts.push_back(newContact);
}

void CollisionTester::testCollisionCirclePoly(Body* a, Body* b) {
    minD = -1.0f;
    for (int i = 0; i < b->getShape()->getPointCount(); i++) {
        vb = b->getPoint(i + 1 == b->getShape()->getPointCount() ? 0 : i + 1) - b->getPoint(i);
        t = (math::dotProduct(math::normalize(vb), a->getPosition()) -
            math::dotProduct(b->getPoint(i), math::normalize(vb))) / math::abs(vb);
        if (t <= 0.0f) point = b->getPoint(i);
        if (t >= 1.0f) point = b->getPoint(i + 1 == b->getShape()->getPointCount() ? 0 : i + 1);
        if (t > 0.0f && t < 1.0f) point = b->getPoint(i) + t * vb;
        d = math::abs(point - a->getPosition());
        if (minD == -1.0f || d < minD) {
            minD = d;
            closestPoint = point;
        }
    }
    if (minD > a->getRadius()) return;
    newContact = new Contact();
    newContact->bodies[0] = a;
    newContact->bodies[1] = b;
    newContact->contactNormal = math::normalize(closestPoint - a->getPosition());
    newContact->contactPoint = closestPoint;
    newContact->penetration = a->getRadius() - minD;
    contacts.push_back(newContact);
}

void CollisionTester::testCollisionNarrow(Body* a, Body* b) {
    if (a->getShapeType() == eShapeType::CIRCLE && b->getShapeType() == eShapeType::CIRCLE) {
        testCollisionCircleCircle(a, b);
    }
    if (a->getShapeType() == eShapeType::CIRCLE && b->getShapeType() == eShapeType::CONVEX) {
        testCollisionCirclePoly(a, b);
    }
    if (a->getShapeType() == eShapeType::CONVEX && b->getShapeType() == eShapeType::CIRCLE) {
        testCollisionCirclePoly(b, a);
    }
    if (a->getShapeType() == eShapeType::CONVEX && b->getShapeType() == eShapeType::CONVEX) {
        testColissionPolyPoly(a, b);
    }
}

void CollisionTester::findCollisions(void) {
    contacts.clear();
    std::sort(AABBs.begin(), AABBs.end(), cmpAABBs);

    mean.x = 0;
    mean.y = 0;
    meanSqrs.x = 0, meanSqrs.y = 0;
    variance.x = 0, variance.y = 0;

    for (int i = 0; i < AABBs.size() - 1; i++) {
        AABBCentre = 0.5f * (AABBs[i]->min + AABBs[i]->max);

        mean += AABBCentre;
        meanSqrs.x = AABBCentre.x * AABBCentre.x;
        meanSqrs.y = AABBCentre.y * AABBCentre.y;

        for (int j = i + 1; j < AABBs.size(); j++) {
            if (math::getAxis(AABBs[i]->max, sortAxis) >= math::getAxis(AABBs[j]->min, sortAxis)) {
                testCollisionNarrow(bodies[AABBs[i]->bodyIndex], bodies[AABBs[j]->bodyIndex]);
            }
            else {
                break;
            }
        }
    }

    variance.x = meanSqrs.x - mean.x * mean.x;
    variance.y = meanSqrs.y - mean.y * mean.y;

    sortAxis = variance.y > variance.x ? 1 : 0;
}

void CollisionTester::updatePositions(void) {
    for (AABB* aabb : AABBs) {
        aabb->setPosition(bodies[aabb->bodyIndex]->getBoundRect());
    }
}

void CollisionTester::appendAABB(sf::FloatRect rect, int bodyIndex) {
    AABBs.push_back(new AABB(rect, bodyIndex));
}

CollisionTester::CollisionTester(std::vector<Body*>& bodies, std::vector<Contact*>& contacts) :
    bodies(bodies), contacts(contacts) {}