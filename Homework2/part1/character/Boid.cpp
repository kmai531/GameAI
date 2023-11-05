#include "Boid.hpp"

Boid::Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos)
{
    window = w;
    if(boidTexture.loadFromFile(tex)) {
        sprite.setTexture(boidTexture);
    } else {
        exit(EXIT_FAILURE);
    }
    sprite.setScale(0.2, 0.2);

    myKinematic = Kinematic();
    mouseVelocityMatching = VelocityMatching();

    
    myKinematic.position = initialPos; 
    myKinematic.velocity = sf::Vector2f(60.f, 0.f);
    sprite.setPosition(initialPos);

    //breadcrumbs
    dropTimer = 2.f;
    crumbIdx = 0;
    breadCrumbs = new vector<Crumb>;
    for(int i = 0; i < 7; i++) {
        Crumb c(i);
        breadCrumbs->push_back(c);
    }
}

void Boid::draw()
{
    window->draw(sprite);
}



Kinematic Boid::getMyKinematic()
{
    return myKinematic;
}

void Boid::update(Kinematic goal, float delTime)
{   
    if(dropTimer > 0){
        dropTimer -= 1;
    }
    else {
        dropTimer = 2.f;
        breadCrumbs->at(crumbIdx).drop(myKinematic.position);
        if(crumbIdx < 6) {
            crumbIdx++;
        }
        else {
            crumbIdx = 0;
        }
    }
    myKinematic.update(mouseVelocityMatching.calculateAcceleration(myKinematic, goal), 10000.f, delTime);
    sprite.setPosition(myKinematic.position);
}   


Boid::~Boid()
{

}