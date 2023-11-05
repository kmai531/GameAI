#pragma once
#include "../SteeringBehavior.hpp"

class Align : public SteeringBehavior
{
    private:
        float targetRadius;
        float slowRadius;
        float maxRotation;
        float maxAngularRotation;
        float timeToTarget;
    public:
        Align(float tRadius, float sRadius, float maxRot, float maxAng);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic target) override;
        float mapToRange(float theta);
};