#include "../hpp/Physics.hpp"

void Physics::check_boundary_helper(Ball&b,const float width,const float height)
{
    sf::CircleShape* ball=b.get_ball();
    sf::Vector2f& speed=b.get_speed();
    sf::Vector2f pos=ball->getPosition();
    const float r=ball->getRadius();
    if(pos.x<0)
    {
        pos.x=0;
        speed.x*=-1;
    }
    if(pos.x>width-2*r)
    {
        pos.x=width-2*r;
        speed.x*=-1;
    }
    if(pos.y<0)
    {
        pos.y=0;
        speed.y*=-1;
    }
    if(pos.y>height-2*r)
    {
        pos.y=height-2*r;
        speed.y*=-1;
    }
    ball->setPosition(pos);
}

float Physics::dot(const sf::Vector2f&v1,const sf::Vector2f&v2)
{
    return v1.x*v2.x+v1.y*v2.y;
}

void Physics::collision_handing_helper(Ball&b1,Ball&b2)
{
    sf::CircleShape*ball1=b1.get_ball();
    sf::CircleShape*ball2=b2.get_ball();
    const float m1=b1.get_mass();
    const float m2=b2.get_mass();
    const float r1=ball1->getRadius();
    const float r2=ball2->getRadius();
    sf::Vector2f& v1=b1.get_speed();
    sf::Vector2f& v2=b2.get_speed();
    sf::Vector2f pos1=ball1->getPosition()+sf::Vector2f(r1,r1);
    sf::Vector2f pos2=ball2->getPosition()+sf::Vector2f(r2,r2);
    auto delta=pos1-pos2;
    auto distance=sqrt(delta.x*delta.x+delta.y*delta.y);
    float over=r1+r2-distance;
    if(over>=0.0f&&distance>=1e-6)
    {
        sf::Vector2f n(delta.x/distance,delta.y/distance);
        auto push=0.5f*over;
        ball1->move(n*push);
        ball2->move(-n*push);

        auto v1n=n*(dot(v1,n));
        auto v1t=v1-v1n;
        auto v2n=n*(dot(v2,n));
        auto v2t=v2-v2n;

        auto v1n_after=(v1n*(m1-m2)+2*m2*v2n)/(m1+m2);
        auto v2n_after=(v2n*(m2-m1)+2*m1*v1n)/(m1+m2);

        v1=v1n_after+v1t;
        v2=v2n_after+v2t;
    }
}

void Physics::check_boundary(Ball&b,const float width,const float height)
{
    check_boundary_helper(b,width,height);
}

void Physics::collision_handing(Ball&b1,Ball&b2)
{
    collision_handing_helper(b1,b2);
}
