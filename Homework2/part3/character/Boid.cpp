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

    maxSpeed = 50.f;
    maxAcceleration = 10000.f;

    maxRotation = 5.f;
    maxAngularAcceleration = 10000.f;

    wanderOffset = 250.f;
    wanderRadius = 250.f;
    wanderRate = 100.f;

    myKinematic->position = initialPos; 
    myKinematic->velocity = sf::Vector2f(0.f, 0.f);
    sprite.setPosition(initialPos.x + sprite.getLocalBounds().width, initialPos.y + sprite.getLocalBounds().height / 2);
    
    arrive = new ArriveBehavior(0.05, 250.f, maxSpeed, maxAcceleration);
    allignRotation = new AllignBehavior( 0.0001f, 1.5f, maxRotation, maxAngularAcceleration);
    mouseVelocityMatching = VelocityMatching();
    wander = new WanderBehavior(wanderOffset, wanderRadius, wanderRate, arrive, allignRotation);
    
    //breadcrumbs
    dropTimer = 10.f;
    crumbIdx = 0;
    breadCrumbs = new vector<Crumb>;
    //cout << "?" << endl;
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
    //myKinematic->update(mouseVelocityMatching.calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    // myKinematic->update(mouseClickArrive->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    // myKinematic->update(allignRotation->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    if(dropTimer > 0){
        dropTimer -= 0.5;
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

    myKinematic->update(wander->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    
    sprite.setPosition(myKinematic->position);
    sprite.setRotation(myKinematic->oreientation * (180.0 / M_PI));
    
}


Boid::~Boid()
{

}