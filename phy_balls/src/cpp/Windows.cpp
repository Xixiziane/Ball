#include "../hpp/Windows.hpp"

Windows::Windows(sf::VideoMode mode,const std::string& title,const std::vector<Ball>&balls_,const Ball_Play&player_):player(player_)
{
    w=new sf::RenderWindow(mode,title);
    for(auto& b:balls_)
    {
        balls.push_back(b);
    }
    prev_ball_positions.reserve(balls.size());
    capture_previous_positions();
    accumulator=0.0f;
}

Windows::~Windows()
{
    delete w;
    w=nullptr;
}

void Windows::Draw()
{
    constexpr float fixed_dt=1.0f/120.0f;
    const float alpha=(fixed_dt>0.0f) ? (accumulator/fixed_dt) : 0.0f;

    for(decltype(balls.size()) i=0;i!=balls.size();++i)
    {
        sf::CircleShape shape=*(balls[i].get_ball());
        if(i<prev_ball_positions.size())
        {
            const sf::Vector2f current=balls[i].get_ball()->getPosition();
            shape.setPosition(prev_ball_positions[i]+(current-prev_ball_positions[i])*alpha);
        }
        w->draw(shape);
    }

    sf::CircleShape player_shape=*(player.get_ball().get_ball());
    const sf::Vector2f current_player_pos=player.get_ball().get_ball()->getPosition();
    player_shape.setPosition(prev_player_position+(current_player_pos-prev_player_position)*alpha);
    w->draw(player_shape);
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

void Windows::capture_previous_positions()
{
    prev_ball_positions.clear();
    prev_ball_positions.reserve(balls.size());
    for(auto& b:balls)
    {
        prev_ball_positions.push_back(b.get_ball()->getPosition());
    }
    prev_player_position=player.get_ball().get_ball()->getPosition();
}

void Windows::fixed_update(const float dt)
{
    player.controler(dt);
    for(auto& b:balls)
    {
        b.get_ball()->move(dt*b.get_speed());
    }

    for(decltype(balls.size()) i=0;i!=balls.size();++i)
    {
        for(decltype(balls.size()) j=i+1;j!=balls.size();++j)
        {
            Physics::collision_handing(balls[i],balls[j]);
        }
        Physics::collision_handing(balls[i],player.get_ball());
    }

    sf::Vector2u size=w->getSize();
    Physics::check_boundary(player.get_ball(),size.x,size.y);
    for(auto& b:balls)
    {
        Physics::check_boundary(b,size.x,size.y);
    }
}

void Windows::run(const float dt)
{
    if(dt<=0.0f)
    {
        return;
    }

    constexpr float fixed_dt=1.0f/120.0f;
    accumulator+=dt;

    while(accumulator>=fixed_dt)
    {
        capture_previous_positions();
        fixed_update(fixed_dt);
        accumulator-=fixed_dt;
    }
}
