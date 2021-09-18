#include "header.h"
#include "warp.h"

Warp::Warp(sf::Vector2f position, int direction, int index)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    if (direction == 1 || direction == 2 || direction == 5 || direction == 6)
    {
        body.setPosition(sf::Vector2f(position.x + 16.0f, position.y));
    }
    else
    {
        body.setPosition(position);
    }
    this->direction = direction;
    this->index = index;
}

Warp::~Warp()
{
    //dtor
}

int Warp::GetWarp()
{
    for (int i = 0; i < warps.size(); i++)
    {
        if (warps[i].index == index)
        {
            if (warps[i].GetPosition().x != body.getPosition().x || warps[i].GetPosition().y != body.getPosition().y)
            {
                return i;
            }
        }
    }

    return -1;
}

void Warp::Update(float deltaTime)
{

}
