#pragma once

#include <SFML/Graphics.hpp>

class BlockParticle
{
    public:
        BlockParticle(sf::Vector2f position, int index);
        ~BlockParticle();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

        bool isOutside;

    private:
        sf::RectangleShape body;
        sf::Vector2f velocity;
};

