#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

class SteeringOutput
{
    public:
        sf::Vector2f linearAcceleration;
        float angularAcceleration;
    SteeringOutput()
    {
        linearAcceleration = sf::Vector2f(0.f, 0.f);
        angularAcceleration = 0;
    }
};

class Kinematic
{
    private: 
        int id;
    public:
        sf::Vector2f position;
        float oreientation;
        
        sf::Vector2f velocity;
        float rotation;

        Kinematic();
        ~Kinematic(){}
        void update(SteeringOutput steering, float maxSpeed, float maxAccelereation, float maxRotation, float maxAngular, float delTime);
        sf::Vector2f normalize(sf::Vector2f vector);
        float vectorLength(sf::Vector2f vector);
        void printInfo();
        int random(int low, int high);
        void setId(int i);
        int getId();
};