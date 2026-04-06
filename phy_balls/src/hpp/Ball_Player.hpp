#pragma once
#include "Ball.hpp"

class Ball_Play
{
private:
    Ball ball_play;

public:
    Ball_Play(const Ball& ball_play_);
    Ball& get_ball();
    void controler(const float dt);
};