#include "Kinematic.hpp"

Kinematic::Kinematic()
{
    id = -1;

    position = sf::Vector2f(0.f, 0.f);
    oreientation = 0;

    velocity = sf::Vector2f(0.f, 0.f);
    rotation = 0;
}

void Kinematic::update(SteeringOutput steering, float maxSpeed, float maxAccelereation, float maxRotation, float maxAngular, float delTime)
{
    //clip

    // std::cout << steering.linearAcceleration.x << " "  << steering.linearAcceleration.y << std::endl;
    if(vectorLength(steering.linearAcceleration) > maxAccelereation) {
        steering.linearAcceleration = normalize(steering.linearAcceleration);
        steering.linearAcceleration *= maxAccelereation;
    }

    float angularAcceleration = fabs(steering.angularAcceleration);
    if(angularAcceleration > maxAngular) {
        steering.angularAcceleration /= angularAcceleration;
        steering.angularAcceleration *= maxAngular;
        
    }

    //update position and orientation
    position += velocity * delTime;
    oreientation += rotation * delTime;

    

    //update velocity and rotation
    velocity += steering.linearAcceleration * delTime;
    // if(steering.linearAcceleration.x == 0)
    //             std::cout << steering.linearAcceleration.y * delTime << std::endl;
    // std::cout << "velocity: " << velocity.y << std::endl;
    // exit(1);
    rotation += steering.angularAcceleration * delTime;
    if(vectorLength(velocity) > maxSpeed) {
        velocity = normalize(velocity);
        velocity *= maxSpeed;
    }
    //check for position out of bounds
    // if(position.x > 650)
    //     position.x = 0;
    // else if(position.x < -10)
    //     position.x = 640;
    // if(position.y > 490)
    //     position.y = 0;
    // else if(position.y < -10)
    //     position.y = 480;
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

void Kinematic::printInfo()
{
    std::cout << "pos: " << position.x << ", " << position.y << " vel: " << velocity.x << ", " << velocity.y << " orientation: " << oreientation << " rotation: " << rotation << std::endl;
}

int Kinematic::random(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(low, high);
    return distr(gen);
}

void Kinematic::setId(int i)
{
    id = i;
}

int Kinematic::getId()
{
    return id;
}