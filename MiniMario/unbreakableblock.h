#pragma once

#include <SFML/Graphics.hpp>

class UnbreakableBlock
{
    public:
        UnbreakableBlock(sf::Vector2f position, int type);
        ~UnbreakableBlock();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        int GetType() {return type;}

        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int column;
        int type;
        int collideCounter;
};
