#pragma once
#include "../../character/Boid.hpp"

class Alignment : public SteeringBehavior
{
    private:
        float visualRange;
        VelocityMatching *velocityMatching;
        vector<Boid *> *boids;
    public:
        Alignment(float vRange, VelocityMatching *vMatch, vector<Boid *> *b);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic target) override;
};