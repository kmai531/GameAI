#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

using namespace std;

int main()
{
    //create a window
    sf::RenderWindow window(sf::VideoMode(640, 480), "CSC 484 HW1 Part3");

    sf::Texture texture1;
    if(!texture1.loadFromFile("resources/boid-sm.png")) 
    {
        exit(1);
    }

    int iteration = 0;

    //boid setup
    list<sf::Sprite> boids;
    boids.push_back(sf::Sprite(texture1));
    boids.back().setPosition(0.f, 0.f);
    boids.back().setScale(2.f, 2.f);
    int count = 1;

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
            list<sf::Sprite>::iterator i = boids.begin();
            while (i != boids.end())
            {
                //movement update
                if(i->getRotation() == 0) 
                {
                    i->move(20.f, 0.f);
                } 
                else if(i->getRotation() == 90) 
                {
                    i->move(0.f, 15.f);
                } 
                else if(i->getRotation() == 180) 
                {
                    i->move(-20.f, 0.f);
                }
                else if(i->getRotation() == 270) 
                {
                    i->move(0.f, -15.f);
                }
                
                //rotation update
                if(i->getPosition().x >= 640 && i->getRotation() == 0) 
                {
                    i->setPosition(640.f, i->getPosition().y);
                    i->setRotation(90);
                    if(count == 1) {
                        boids.push_back(sf::Sprite(texture1));
                        boids.back().setPosition(0.f, 0.f);
                        boids.back().setScale(2.f, 2.f);
                        count++;
                    }
                }
                else if(i->getPosition().y >= 480 && i->getRotation() == 90) 
                {
                    i->setPosition(i->getPosition().x, 480.f);
                    i->setRotation(180);
                    if(count == 2) {
                        boids.push_back(sf::Sprite(texture1));
                        boids.back().setPosition(0.f, 0.f);
                        boids.back().setScale(2.f, 2.f);
                        count++;
                    }
                }
                else if(i->getPosition().x <= 0 && i->getRotation() == 180) 
                {
                    i->setPosition(0.f, i->getPosition().y);
                    i->setRotation(270);
                    if(count == 3) {
                        boids.push_back(sf::Sprite(texture1));
                        boids.back().setPosition(0.f, 0.f);
                        boids.back().setScale(2.f, 2.f);
                        count++;
                    }
                }
                else if(i->getPosition().x == 0 && i->getPosition().y == 0 && i->getRotation() == 270) 
                {
                    i = boids.erase(i);
                }
                ++i;
            } //end of list iterator loop
        } //end of iteration if statement
        
        if(boids.size() == 0) 
        {
            boids.push_back(sf::Sprite(texture1));
            boids.back().setPosition(0.f, 0.f);
            boids.back().setScale(2.f, 2.f);
            count = 1;
        }

        //draw
        window.clear(sf::Color(150, 153, 146));
        for(auto &i : boids)
        {
            window.draw(i);
        }
        window.display();
        ++iteration;

    } //end of window while loop
    return 0;
}