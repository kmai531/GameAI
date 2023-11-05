#include "Boid.hpp"

Boid::Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos)
{
    window = w;
    if(boidTexture.loadFromFile(tex)) {
        sprite.setTexture(boidTexture);
    } else {
        exit(EXIT_FAILURE);
    }
    sprite.setScale(0.02, 0.02);
    
    sprite.setOrigin(0, sprite.getLocalBounds().height / 2);
    myKinematic = new Kinematic();

    maxSpeed = 100.f;
    maxAcceleration = 1000.f;

    maxRotation = 8.f;
    maxAngularAcceleration = 10000.f;

    wanderOffset = 90.f;
    wanderRadius = 60.f;
    wanderRate = 1.25f;

    myKinematic->position = initialPos; 

    float vX = myKinematic->random(-150, 150);
    float vY = myKinematic->random(-150, 150);

    if(vX == 0 || vY == 0) {
        vX = 150;
        vY = 150;
    }
    
    myKinematic->velocity = sf::Vector2f(vX, vY);
    sprite.setPosition(initialPos);
    
    float initialOrientation = atan2(vY, vX);
    myKinematic->oreientation = initialOrientation;

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



Kinematic* Boid::getMyKinematic()
{
    return myKinematic;
}

void Boid::update(Kinematic goal, float delTime)
{    
    sprite.setPosition(myKinematic->position);
    sprite.setRotation(myKinematic->oreientation * (180.0 / M_PI));
}


void Boid::updateFromSteeringOutput(SteeringOutput input, float delTime) 
{
    if(dropTimer > 0){
        dropTimer -= 1;
    }
    else {
        dropTimer = 2.f;
        breadCrumbs->at(crumbIdx).drop(myKinematic->position);
        if(crumbIdx < 6) {
            crumbIdx++;
        }
        else {
            crumbIdx = 0;
        }
    }
    
    myKinematic->update(input, maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    sprite.setPosition(myKinematic->position);
    sprite.setRotation(myKinematic->oreientation * (180.0 / M_PI));
    if(myKinematic->position.x > 650) {
        myKinematic->position.x = -10;
    }
        
    else if(myKinematic->position.x < -10) {
        myKinematic->position.x = 650;  
    }
        
    if(myKinematic->position.y > 490) {
        myKinematic->position.y = -10;
    }
        
    else if(myKinematic->position.y < -10) {
        myKinematic->position.y = 480;
    }
        
}

Boid::~Boid()
{

}
