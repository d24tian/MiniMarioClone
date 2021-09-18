#pragma once

#include <SFML/Graphics.hpp>

class CoinIcon
{
    public:
        CoinIcon();
        ~CoinIcon();

        void SetPosition(float x, float y) {body.setPosition(sf::Vector2f(x, y));};
        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int columnBegin;
        unsigned int columnEnd;
};
