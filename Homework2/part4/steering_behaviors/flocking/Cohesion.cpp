#include "Cohesion.hpp"

Cohesion::Cohesion(float vRange, Seek *seek, vector<Boid *> *b)
{
    visualRange = vRange;
    positionMatching = seek;
    boids = b;
}

SteeringOutput Cohesion::calculateAcceleration(Kinematic character, Kinematic target)
{
    SteeringOutput result;

    sf::Vector2f center(0.f, 0.f);
    float numNeighbors = 0;

    //loop through all other boids
    for(int i = 0; i < boids->size(); i++) {
        //dont count urself
        if(boids->at(i)->getMyKinematic()->getId() == character.getId()) {
            continue;
        }
        
        sf::Vector2f direction = boids->at(i)->getMyKinematic()->position - character.position;
        float distance = character.vectorLength(direction);

        if(distance < visualRange) {
            center += boids->at(i)->getMyKinematic()->position;
            numNeighbors++;
        }
    }
    
    if(numNeighbors > 0) {
        center /= numNeighbors;
        Kinematic goal;
        goal.position = center;
        result = positionMatching->calculateAcceleration(character, goal);
    }
    
    return result;
}