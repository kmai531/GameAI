#pragma once

#include "SteeringBehavior.hpp"
#include "ArriveBehavior.hpp"
#include "AllignBehavior.hpp"
#include <random>

class WanderBehavior : SteeringBehavior
{
    private:
        float wanderOffset;
        float wanderRadius;
        float wanderRate;
        
        ArriveBehavior *arriveBehavior;
        AllignBehavior *allignBehavior;

    public:
        WanderBehavior(float wOffset, float wRadius, float wRate, ArriveBehavior *arrive, AllignBehavior *allignw);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal) override;
        float randomBinomial();
        double random(int low, int high);
};