#include "Align.hpp"

Align::Align(float tRadius, float sRadius, float maxRot, float maxAng)
{
    targetRadius = tRadius;
    slowRadius = sRadius;
    maxRotation = maxRot;
    maxAngularRotation = maxAng;
    timeToTarget = 1.f / 60.f;
}

SteeringOutput Align::calculateAcceleration(Kinematic character, Kinematic target)
{
    SteeringOutput result;
    float rotation = target.oreientation - character.oreientation;

    rotation = mapToRange(rotation);

    float rotationSize = fabs(rotation);

    if(rotationSize < targetRadius) {
        result.angularAcceleration = 0;
        result.linearAcceleration = sf::Vector2f(0, 0);
        return result;
    }

    float targetRotation;
    if(rotationSize > slowRadius) {
        targetRotation = maxRotation;
    }
    else {
        targetRotation = maxRotation * rotationSize / slowRadius;
    }

    targetRotation *= rotation / rotationSize;
    
    result.angularAcceleration = targetRotation - character.rotation;
    result.angularAcceleration /= timeToTarget;

    return result;
}

float Align::mapToRange(float theta)
{
    float r = fmod(theta, (2 * M_PI));
    if(fabs(r) <= M_PI) {
        return r;
    }
    if(r > M_PI) {
        return r - 2 * M_PI;
    }
    else {
        return 2 * M_PI + r;
    }
}