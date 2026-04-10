#pragma once
#include"Ball.hpp"
#include"Physics.hpp"
#include"Ball_Player.hpp"
#include<string>
#include<vector>


class Windows   
{
    private:
    sf::RenderWindow *w;
    std::vector<Ball> balls;
    Ball_Play player;
    std::vector<sf::Vector2f> prev_ball_positions;
    sf::Vector2f prev_player_position;
    float accumulator;

    void capture_previous_positions();
    void fixed_update(const float dt);
    public:
    Windows(sf::VideoMode mode,const std::string& title,const std::vector<Ball>&balls_,const Ball_Play&player_);
    Windows(const Windows&other)=delete;
    Windows& operator=(const Windows&other)=delete;
    ~Windows();
    void Draw();
    void display();
    void clear(const sf::Color& color);
    sf::RenderWindow*get_windows();
    void run(const float dt);
};