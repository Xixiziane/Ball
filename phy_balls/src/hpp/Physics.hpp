#pragma once
#include"Ball.hpp"
#include<cmath>
class Physics
{
    private:    
    static void check_boundary_helper(Ball&b,const float width,const float height);
    static float dot(const sf::Vector2f&v1,const sf::Vector2f&v2);
    static void collision_handing_helper(Ball&b1,Ball&b2);
    public:
    static void check_boundary(Ball&b,const float width,const float height);
    static void collision_handing(Ball&b1,Ball&b2);
};