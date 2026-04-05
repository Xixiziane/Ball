#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
    private:
    sf::CircleShape *ball;
    sf::Vector2f speed;
    float m;
    public:
    Ball(const sf::CircleShape&ball_,const sf::Vector2f&speed_,const float &m_);
    ~Ball();
    Ball(const Ball &other);
    sf::Vector2f& get_speed();
    sf::CircleShape* get_ball();
    float get_mass() const;
};