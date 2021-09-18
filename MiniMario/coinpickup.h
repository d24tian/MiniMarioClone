#pragma once

#include <SFML/Graphics.hpp>

class CoinPickup
{
    public:
        CoinPickup(sf::Texture* texture, sf::Vector2f position);
        ~CoinPickup();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

    private:
        sf::RectangleShape body;
        Animation animation;
};

