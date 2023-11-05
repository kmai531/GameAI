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
    texture.loadFromFile("resources/boid.png");

    Boid b = Boid(&window, "resources/boid.png", sf::Vector2f(50.f, 200.f));
    Boid target = Boid(&window, "resources/boid.png", sf::Vector2f(-490, 0));
    //target.sprite.setOrigin(target.sprite.getGlobalBounds().width / 2.0f, target.sprite.getGlobalBounds().height / 2.0f);

    // sf::RectangleShape shape;
    // shape.setFillColor(sf::Color::Red);
    // shape.setSize(sf::Vector2f(100.f, 50.f));
    // shape.setOrigin(50.f, 25.f);
    // shape.setPosition(300, 300);

    sf::Sprite shape;
    shape.setTexture(texture);
    shape.setScale(sf::Vector2f(0.2f, 0.2f));
    shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
    shape.setPosition(300, 300);
    //Game time
    GameTimeLine gameTimeLine(1.f);
    float currentTime, lastTime = gameTimeLine.getTime();
    float elapsedTime = 8e-12;
    int iteration = 0;

    // sf::Clock clock;
    // float lastFrameTime = 0.f;
    sf::Vector2f mousePosition;
    Kinematic mouse;
    mouse.position = b.getMyKinematic()->position;

    //target.getMyKinematic()->oreientation = 90.0f * (M_PI / 180.0f);
    
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                    // mouse.position = mousePosition;
                    
                    // float degree = atan2(mousePosition.y - b.getMyKinematic()->position.y, mousePosition.x - b.getMyKinematic()->position.x);
                    // std::cout << "mouse click position: " << mouse.position.x << ", " << mouse.position.y << " player position: " << b.getMyKinematic()->position.x << ", " << b.getMyKinematic()->position.y << " degree: " << degree << std::endl;
                    // mouse.oreientation = degree;
                }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            shape.rotate(-10);
            target.sprite.rotate(-10);
        }
        
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            shape.rotate(10);
            target.sprite.rotate(10);
        }

        else {
            shape.rotate(0);
            target.sprite.rotate(0);
        }
            
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            mouse.position = mousePosition;
            
            float degree = atan2(mousePosition.y - b.getMyKinematic()->position.y, mousePosition.x - b.getMyKinematic()->position.x);
            //std::cout << "mouse click position: " << mouse.position.x << ", " << mouse.position.y << " player position: " << b.getMyKinematic()->position.x << ", " << b.getMyKinematic()->position.y << " degree: " << degree << std::endl;
            mouse.oreientation = degree;
        }
        //game time update
        
        currentTime = gameTimeLine.getTime();
        if(iteration != 0)
            elapsedTime= (currentTime - lastTime);

        


        b.update(mouse, elapsedTime);

        //cout << "character: " << b.getMyKinematic()->oreientation * (180.0 / M_PI)<< " mouse: " << mouse.oreientation * (180.0 / M_PI)<< endl;
        window.clear(sf::Color(150, 153, 146));

        for(int i = 0; i < b.breadCrumbs->size(); i++) {
            b.breadCrumbs->at(i).draw(&window);
        }
        b.draw();
        //target.draw();

        //window.draw(shape);
        window.display();


        //lastFrameTime = currentFrameTime;
        lastTime = currentTime;
        ++iteration;
    }

    return 0;
}