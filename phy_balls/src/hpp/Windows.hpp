#pragma once
#include"Ball.hpp"
#include "Physics.hpp"
#include<string>
#include<vector>

class Windows   
{
    private:
    sf::RenderWindow *w;
    std::vector<Ball> balls;
    public:
    Windows(sf::VideoMode mode,const std::string& title,const std::vector<Ball>&balls_);
    Windows(const Windows&other)=delete;
    Windows& operator=(const Windows&other)=delete;
    ~Windows();
    void Draw();
    void display();
    void clear(const sf::Color& color);
    sf::RenderWindow*get_windows();
    void run(const float dt);
};