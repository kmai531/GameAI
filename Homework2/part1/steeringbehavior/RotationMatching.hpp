#pragma once
#include "SteeringBehavior.hpp"
class RotationMatching : public SteeringBehavior
{
    public:
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal) override;
};