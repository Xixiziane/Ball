#include "../hpp/Ball.hpp"

Ball::Ball(const sf::CircleShape&ball_,const sf::Vector2f&speed_,const float &m_)
{
    ball=new sf::CircleShape(ball_);
    speed=speed_;
    m=m_;
}

Ball::~Ball()
{
    delete ball;
    ball =nullptr;
}

Ball::Ball(const Ball &other)
{
    ball=new sf::CircleShape(*(other.ball));
    speed=other.speed;
    m=other.m;
}

sf::Vector2f& Ball::get_speed()
{
    return speed;
}

sf::CircleShape* Ball::get_ball()
{
    return ball;
}

float Ball::get_mass() const
{
    return m;
}
