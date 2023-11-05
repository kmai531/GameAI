#pragma once
#include "../steering_behaviors/position_matching/Seek.hpp"
#include "../steering_behaviors/velocity_matching/VelocityMatching.hpp"
#include "BreadCrumb.hpp"

class Boid
{
    private:
        
        sf::RenderWindow *window;
        sf::Texture boidTexture;

        Kinematic *myKinematic;

        float maxSpeed;
        float maxAcceleration;

        float maxRotation;
        float maxAngularAcceleration;

        float wanderOffset;
        float wanderRadius;
        float wanderRate;

        float dropTimer;
        
        int crumbIdx;


    public:
        sf::Sprite sprite;
        Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos);
        ~Boid();
        
        void draw();
        void update(Kinematic goal, float delTime);
        void updateFromSteeringOutput(SteeringOutput input, float delTime);

        Kinematic* getMyKinematic();
        void move();

        vector<Crumb>* breadCrumbs;
};