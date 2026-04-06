#include "../hpp/Windows.hpp"

Windows::Windows(sf::VideoMode mode,const std::string& title,const std::vector<Ball>&balls_,const Ball_Play&player_):player(player_)
{
    w=new sf::RenderWindow(mode,title);
    for(auto& b:balls_)
    {
        balls.push_back(b);
    }
}

Windows::~Windows()
{
    delete w;
    w=nullptr;
}

void Windows::Draw()
{
    for(auto &b:balls)
    {
        w->draw(*(b.get_ball()));
    }
    w->draw(*(player.get_ball().get_ball()));
}

void Windows::display()
{
    w->display();
}

void Windows::clear(const sf::Color& color)
{
    w->clear(color);
}

sf::RenderWindow* Windows::get_windows()
{
    return w;
}

void Windows::run(const float dt)
{
    sf::Vector2u size=w->getSize();
    player.controler(dt);
    for(auto&b:balls)
    {
        b.get_ball()->move(dt*b.get_speed());
    }

    for(decltype(balls.size())i=0;i!=balls.size();++i)
    {
        for(decltype(balls.size())j=i+1;j!=balls.size();++j)
        {
            Physics::collision_handing(balls[i],balls[j]);
        }
        Physics::collision_handing(balls[i],player.get_ball());
    }
    Physics::check_boundary(player.get_ball(),size.x,size.y);
    for(auto&b:balls)
    {
        Physics::check_boundary(b,size.x,size.y);
    }
}
