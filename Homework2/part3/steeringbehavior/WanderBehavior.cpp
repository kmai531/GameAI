#include "WanderBehavior.hpp"
#include "ArriveBehavior.hpp"

WanderBehavior::WanderBehavior(float wOffset, float wRadius, float wRate, ArriveBehavior *arrive, AllignBehavior *allign)
{
    wanderOffset = wOffset;
    wanderRadius = wRadius;
    wanderRate = wRate;
    arriveBehavior = arrive;
    allignBehavior = allign;
}

SteeringOutput WanderBehavior::calculateAcceleration(Kinematic character, Kinematic goal)
{
    SteeringOutput result;

    float wanderOrientation = wanderRate * randomBinomial();
    
    float targetOrientation = character.oreientation - wanderOrientation;
    sf::Vector2f target = character.position + wanderOffset * sf::Vector2f(std::cos(character.oreientation), std::sin(character.oreientation));
    target += wanderRadius * sf::Vector2f(std::cos(targetOrientation), std::sin(targetOrientation));
    Kinematic targetKinematic;
    targetKinematic.position = target;

    float degree = atan2(targetKinematic.position.y - character.position.y, targetKinematic.position.x - character.position.x);
    targetKinematic.oreientation = degree;
    result.linearAcceleration = arriveBehavior->calculateAcceleration(character, targetKinematic).linearAcceleration;
    result.angularAcceleration = allignBehavior->calculateAcceleration(character, targetKinematic).angularAcceleration;
    return result;
}

float WanderBehavior::randomBinomial()
{
    return random(0, 1) - random(0, 1);
}



double WanderBehavior::random(int low, int high) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    return dis(gen);
}