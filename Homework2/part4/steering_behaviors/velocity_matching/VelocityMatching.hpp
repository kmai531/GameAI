#pragma once
#include "../SteeringBehavior.hpp"

class VelocityMatching : public SteeringBehavior
{
    public:
        VelocityMatching() {}
        ~VelocityMatching() {}
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic target) override;
};