#pragma once

#include "animation.h"
#include <SFML/Graphics.hpp>

class Coin
{
    public:
        Coin(sf::Vector2f position);
         ~Coin();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

        int movement;

    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int columnBegin;
        unsigned int columnEnd;
        float moveTimer;
        sf::Vector2f velocity;
        float originalY;
};
