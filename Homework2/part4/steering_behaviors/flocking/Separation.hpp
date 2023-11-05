#pragma once
#include "../../character/Boid.hpp"

class Separation : public SteeringBehavior
{
    private:
        float threshold;
        vector<Boid *> *boids;
    public:
        Separation(float range, vector<Boid *> *b);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic target) override;
};