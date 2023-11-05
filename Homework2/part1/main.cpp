#include "character/Boid.hpp"
#include "time/GameTimeLine.hpp"
#include "steeringbehavior/VelocityMatching.hpp"
using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(640, 480), "CSC 484 HW2 Part1", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Texture texture;

    Boid b = Boid(&window, "resources/boid-high.png", sf::Vector2f(0.f, 200.f));

    //Game time
    GameTimeLine gameTimeLine(1.f);
    float currentTime, lastTime = gameTimeLine.getTime();
    float elapsedTime = 8e-12;
    int iteration = 0;

    // sf::Clock clock;
    // float lastFrameTime = 0.f;

    //sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
    sf::Vector2i lastMousePosition = sf::Mouse::getPosition(window);
    std::cout << "initial: " << lastMousePosition.x << endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //game time update
        currentTime = gameTimeLine.getTime();
        if(iteration != 0)
            elapsedTime= (currentTime - lastTime);


        sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
        sf::Vector2i mouseDisplacement = currentMousePosition - lastMousePosition;
        

        //std::cout << "Elapsed time: " << elapsedTime << " seconds" << std::endl;
        

        sf::Vector2f mouseVelocity = (sf::Vector2f(mouseDisplacement.x / elapsedTime, mouseDisplacement.y / elapsedTime));
        //std::cout << "Mouse velocity: " << mouseVelocity.x << ", " << mouseVelocity.y << std::endl;

        Kinematic mouseKinematic;
        mouseKinematic.velocity = mouseVelocity;
        b.update(mouseKinematic, elapsedTime);
        float vel = mouseKinematic.vectorLength(mouseKinematic.velocity);
        //if(vel > 10000)
        //std::cout << vel << std::endl;
        
        window.clear(sf::Color(150, 153, 146));

        for(int i = 0; i < b.breadCrumbs->size(); i++) {
            b.breadCrumbs->at(i).draw(&window);
        }
        b.draw();
        window.display();


        //lastFrameTime = currentFrameTime;
        lastTime = currentTime;
        lastMousePosition = currentMousePosition;
        ++iteration;
    }

    return 0;
}