#pragma once
#include "../steeringbehavior/VelocityMatching.hpp"
#include "../steeringbehavior/ArriveBehavior.hpp"
#include "../steeringbehavior/AllignBehavior.hpp"
#include "../steeringbehavior/WanderBehavior.hpp"

#include "BreadCrumb.hpp"

using namespace std;

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

        VelocityMatching mouseVelocityMatching;
        ArriveBehavior *arrive;
        AllignBehavior *allignRotation;
        WanderBehavior *wander;
        
        float dropTimer;
        
        int crumbIdx;

    public:
        sf::Sprite sprite;
        Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos);
        ~Boid();
        
        void draw();
        void update(Kinematic goal, float delTime);

        Kinematic* getMyKinematic();
        void move();
        
        vector<Crumb>* breadCrumbs;
};