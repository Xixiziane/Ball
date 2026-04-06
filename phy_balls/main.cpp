#include"src/hpp/Windows.hpp"

const float height=600;
const float width=800;

int main()
{
    std::vector<Ball>balls;
    sf::CircleShape b1(30);
    b1.setFillColor(sf::Color::Blue);
    b1.setPosition(400,300);
    balls.push_back(Ball(b1,sf::Vector2f(20.0f,30.0f),10));
    sf::CircleShape b2(40);
    b2.setFillColor(sf::Color::Green);
    b2.setPosition(400,300);
    balls.push_back(Ball(b2,sf::Vector2f(-30.0f,-40.0f),20));
    sf::CircleShape b3(35);
    b3.setFillColor(sf::Color::Cyan);
    b3.setPosition(200,300);
    Ball ball3(b3,sf::Vector2f(0,0),40);
    Ball_Play play(ball3);
    Windows w(sf::VideoMode(width,height),"SFML",balls,play);
    sf::RenderWindow* windows=w.get_windows();
    windows->setFramerateLimit(60);
    sf::Clock clock;
    while(windows->isOpen())
    {
        sf::Event event;
        while (windows->pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
               windows->close();
        }
        float dt=clock.restart().asSeconds();
        w.run(dt);
        w.clear(sf::Color::White);
        w.Draw();
        w.display();
    }
}