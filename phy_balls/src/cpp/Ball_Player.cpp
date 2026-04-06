#include "../hpp/Ball_Player.hpp"

#include <cmath>

Ball_Play::Ball_Play(const Ball& ball_play_) : ball_play(ball_play_)
{
}

Ball& Ball_Play::get_ball()
{
    return ball_play;
}

void Ball_Play::controler(const float dt)
{
    if(dt <= 0.0f)
    {
        return;
    }

    sf::Vector2f input(0.0f, 0.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        input.y -= 1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        input.y += 1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        input.x -= 1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        input.x += 1.0f;
    }

    float len = std::sqrt(input.x * input.x + input.y * input.y);
    if(len > 1e-5f)
    {
        input /= len;
    }

    sf::Vector2f& speed = ball_play.get_speed();
    constexpr float accel = 1200.0f;
    constexpr float maxSpeed = 280.0f;
    constexpr float dragWhenMove = 7.0f;
    constexpr float dragWhenIdle = 11.0f;

    speed += input * (accel * dt);

    const float drag = (len > 1e-5f) ? dragWhenMove : dragWhenIdle;
    speed *= (1.0f / (1.0f + drag * dt));

    float speedLen = std::sqrt(speed.x * speed.x + speed.y * speed.y);
    if(speedLen > maxSpeed)
    {
        speed *= (maxSpeed / speedLen);
    }

    ball_play.get_ball()->move(speed * dt);
}
