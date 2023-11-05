#include "VelocityMatching.hpp"

SteeringOutput VelocityMatching::calculateAcceleration(Kinematic character, Kinematic target)
{
    SteeringOutput result;
    result.linearAcceleration = target.velocity - character.velocity;
    result.linearAcceleration /= (1.f / 60.f);
    result.angularAcceleration = 0;

    return result;
}