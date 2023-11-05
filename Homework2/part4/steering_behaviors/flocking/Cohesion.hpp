#pragma once
#include "../../character/Boid.hpp"



class Cohesion : public SteeringBehavior
{
    private:
        float visualRange;
        Seek *positionMatching;
        vector<Boid *> *boids;

    public:
        Cohesion(float vRange, Seek *seek, vector<Boid *> *b);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic target) override;
};