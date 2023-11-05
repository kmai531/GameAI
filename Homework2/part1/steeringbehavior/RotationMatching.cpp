#include "RotationMatching.hpp"

SteeringOutput RotationMatching::calculateAcceleration(Kinematic character, Kinematic goal)
{
    SteeringOutput rtn;

    rtn.angularAcceleration = goal.rotation - character.rotation;
    rtn.linearAcceleration = sf::Vector2f(0, 0);
    return rtn;
}