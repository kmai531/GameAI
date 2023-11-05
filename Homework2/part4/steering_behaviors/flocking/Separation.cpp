#include "Separation.hpp"

Separation::Separation(float range, vector<Boid *> *b)
{
    threshold = range;
    boids = b;
}

SteeringOutput Separation::calculateAcceleration(Kinematic character, Kinematic target)
{
    SteeringOutput result;

    for(int i = 0; i < boids->size(); i++) {
        if(boids->at(i)->getMyKinematic()->getId() == character.getId()) {
            continue;
        }
        sf::Vector2f direction = character.position - boids->at(i)->getMyKinematic()->position;
        float distance = character.vectorLength(direction);
        if(distance < threshold) {
            //float strength = std::min(600000 / (distance * distance), 1000.f);
            float strength = 4500 * (threshold - distance) / threshold;
            direction = character.normalize(direction);
            result.linearAcceleration += strength * direction;
        }
    }
    return result;
}