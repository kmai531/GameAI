#include "character/Boid.hpp"
#include "steering_behaviors/flocking/Alignment.hpp"
#include "steering_behaviors/flocking/Cohesion.hpp"
#include "steering_behaviors/flocking/Separation.hpp"
#include "steering_behaviors/orientation_matching/Align.hpp"
using namespace std;



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(640, 480), "CSC 484 HW2 Part 4", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    //Game time 
    sf::Clock gameTime;
    float lastTime = 0.f;

    //create boids
    vector<Boid *> *boids = new vector<Boid *>();

    // vector<Crumb> crumbs1 = vector<Crumb>();
    // for(int i = 0; i < 7; i++) {
    //     Crumb c(i);
    //     crumbs1.push_back(c);
    // }
    // vector<Crumb> crumbs2 = vector<Crumb>();
    // for(int i = 0; i < 7; i++) {
    //     Crumb c(i);
    //     crumbs2.push_back(c);
    // }

    boids->emplace_back(new Boid(&window, "resources/boid.png", sf::Vector2f(320, 0)));
    boids->back()->getMyKinematic()->velocity = sf::Vector2f(0, 30);
    boids->back()->getMyKinematic()->setId(1);
    boids->emplace_back(new Boid(&window, "resources/boid.png", sf::Vector2f(0, 240)));
    boids->back()->getMyKinematic()->velocity = sf::Vector2f(40, 0);
    boids->back()->getMyKinematic()->setId(2);

    Kinematic target;
    
    for(int i = 0; i < 50; i++) {
        boids->emplace_back(new Boid(&window, "resources/boid.png", sf::Vector2f(target.random(0, 640), target.random(0, 480))));
        boids->at(i)->getMyKinematic()->setId(i);
    }

    //create behaviors
    VelocityMatching velMatch;
    Seek seek(300);
    Align alignOrientation(0.0001f, 4.f, 15.f, 400.f);

    Separation separate(30, boids);
    Alignment align(31.f, &velMatch, boids);
    Cohesion cohesion(31.f, &seek, boids);
    
    while(window.isOpen()) 
    {
        // Events
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        float currentTime = gameTime.getElapsedTime().asSeconds();
        float elapsedTime = currentTime - lastTime;

        for(int i = 0; i < boids->size(); i++) {
            SteeringOutput total;
            
            SteeringOutput alignOut = align.calculateAcceleration(*boids->at(i)->getMyKinematic(), target);
            SteeringOutput coheOut = cohesion.calculateAcceleration(*boids->at(i)->getMyKinematic(), target);
            SteeringOutput sepOut = separate.calculateAcceleration(*boids->at(i)->getMyKinematic(), target);
            total.linearAcceleration = sepOut.linearAcceleration + alignOut.linearAcceleration + coheOut.linearAcceleration;

            float targetOrientation = atan2(boids->at(i)->getMyKinematic()->velocity.y, boids->at(i)->getMyKinematic()->velocity.x);
            target.oreientation = targetOrientation;
            total.angularAcceleration = alignOrientation.calculateAcceleration(*boids->at(i)->getMyKinematic(), target).angularAcceleration;

            boids->at(i)->updateFromSteeringOutput(total, elapsedTime);
        }


        window.clear(sf::Color(150, 153, 146));

        //draw items
        for(auto i : *boids) {
            for(int j = 0; j < i->breadCrumbs->size(); j++) {
                i->breadCrumbs->at(j).draw(&window);
            }
            i->draw();
        }
        window.display();
        lastTime = currentTime;
    }
}