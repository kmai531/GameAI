#include "Boid.hpp"

Boid::Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos)
{
    window = w;
    if(boidTexture.loadFromFile(tex)) {
        sprite.setTexture(boidTexture);
    } else {
        exit(EXIT_FAILURE);
    }
    sprite.setScale(0.05, 0.05);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    myKinematic = new Kinematic();

    maxSpeed = 200.f;
    maxAcceleration = 10000.f;

    maxRotation = 10.f;
    maxAngularAcceleration = 10000.f;

    myKinematic->position = initialPos; 
    myKinematic->velocity = sf::Vector2f(0.f, 0.f);
    sprite.setPosition(initialPos.x + sprite.getLocalBounds().width, initialPos.y + sprite.getLocalBounds().height / 2);
    
    mouseClickArrive = new ArriveBehavior(0.05, 380.f, maxSpeed, maxAcceleration);
    allignRotation = new AllignBehavior( 0.0001f, 4.f, maxRotation, maxAngularAcceleration);
    mouseVelocityMatching = VelocityMatching();

    //breadcrumbs
    //breadcrumbs
    dropTimer = 10.f;
    crumbIdx = 0;
    breadCrumbs = new vector<Crumb>;
    
    for(int i = 0; i < 17; i++) {
        Crumb c(i);
        breadCrumbs->push_back(c);
    } 
}

void Boid::draw()
{
    window->draw(sprite);
}



Kinematic* Boid::getMyKinematic()
{
    return myKinematic;
}

void Boid::update(Kinematic goal, float delTime)
{   
    if(dropTimer > 0){
        dropTimer -= 1;
    }
    else {
        dropTimer = 10.f;
        breadCrumbs->at(crumbIdx).drop(myKinematic->position);
        if(crumbIdx < 16) {
            crumbIdx++;
        }
        else {
            crumbIdx = 0;
        }
    }
    //myKinematic->update(mouseVelocityMatching.calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    myKinematic->update(mouseClickArrive->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    myKinematic->update(allignRotation->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    sprite.setPosition(myKinematic->position);
    sprite.setRotation(myKinematic->oreientation * (180.0 / M_PI));
    
}


Boid::~Boid()
{

}