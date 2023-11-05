#include <SFML/Graphics.hpp>

int main()
{

    //create a new window
    sf::RenderWindow window(sf::VideoMode(640, 480), "CSC 484 HW1 Part2");

    sf::Texture texture1;
    if(!texture1.loadFromFile("resources/boid-sm.png")) 
    {
        exit(1);
    }
    
    sf::Sprite boid(texture1);
    boid.setScale(2.f, 2.f);

    int iteration = 0;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        
        if(iteration % 100 == 0)
        {
            boid.move(10.f, 0.f);
            if(boid.getPosition().x > 640)
            {
                boid.setPosition(0.f, 0.f);
            }
            
        }

        window.clear(sf::Color(150, 153, 146));
        window.draw(boid);
        window.display();
        ++iteration;
    }
    return 0;
}