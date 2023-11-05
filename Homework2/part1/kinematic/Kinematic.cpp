#include "Kinematic.hpp"

Kinematic::Kinematic()
{
    position = sf::Vector2f(0.f, 0.f);
    oreientation = 0;

    velocity = sf::Vector2f(0.f, 0.f);
    rotation = 0;
}

void Kinematic::update(SteeringOutput steering, float maxSpeed, float delTime)
{
    //update position and orientation
    position += velocity * delTime;
    oreientation += rotation * delTime;

    //update velocity and rotation
    velocity += steering.linearAcceleration * delTime;
    // std::cout << "velocity: " << velocity.y << std::endl;
    // exit(1);
    rotation += steering.angularAcceleration * delTime;
    
    //clip
    if(vectorLength(velocity) > maxSpeed) {
        velocity = normalize(velocity);
        velocity *= maxSpeed;
    }

    //check for position out of bounds
    if(position.x > 650)
        position.x -= 660;
    else if(position.x < -10)
        position.x += 660;
    if(position.y > 490)
        position.y -= 500;
    else if(position.y < -10)
        position.y += 500;
}

float Kinematic::vectorLength(sf::Vector2f vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


sf::Vector2f Kinematic::normalize(sf::Vector2f vector)
{
    float length = vectorLength(vector);
    vector.x /= length;
    vector.y /= length;  
    return vector;
}