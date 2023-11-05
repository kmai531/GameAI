#include "Alignment.hpp"

Alignment::Alignment(float vRange, VelocityMatching *vMatch, vector<Boid *> *b)
{
    visualRange = vRange;
    velocityMatching = vMatch;
    boids = b;
}

SteeringOutput Alignment::calculateAcceleration(Kinematic character, Kinematic target)
{
    SteeringOutput result;

    sf::Vector2f averageVelocity(0.f, 0.f);
    float numNeighbor = 0;

    for(int i = 0; i < boids->size(); i++) {
        if(boids->at(i)->getMyKinematic()->getId() == character.getId()) {
            continue;
        }
        sf::Vector2f direction = boids->at(i)->getMyKinematic()->position - character.position;
        float distance = character.vectorLength(direction);
        if(distance < visualRange) {
            averageVelocity += boids->at(i)->getMyKinematic()->velocity;
            numNeighbor++;
        }
    }
    
    if(numNeighbor > 0) {
        averageVelocity /= numNeighbor;
        Kinematic goal;
        goal.velocity = averageVelocity;
        result = velocityMatching->calculateAcceleration(character, goal);
    }

    return result;
}