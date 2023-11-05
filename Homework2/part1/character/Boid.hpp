#pragma once
#include "../steeringbehavior/VelocityMatching.hpp"
#include "BreadCrumb.hpp"

using namespace std;
class Boid
{
    private:
        sf::Sprite sprite;
        sf::RenderWindow *window;
        Kinematic myKinematic;
        sf::Texture boidTexture;
        VelocityMatching mouseVelocityMatching;
        float dropTimer;
        
        int crumbIdx;

    public:
        Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos);
        ~Boid();
        
        void draw();
        void update(Kinematic goal, float delTime);

        Kinematic getMyKinematic();
        void move();

        vector<Crumb>* breadCrumbs;
};