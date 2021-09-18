#pragma once

#include <SFML/Graphics.hpp>

class Item
{
    public:
        Item(sf::Vector2f position, int type);
        ~Item();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        void Bump();

        /**
        0 = Mushroom
        1 = Fire flower
        2 = Star
        3 = 1-Up
        */
        int type;
        bool bumpCooldown;
        float spawnTimer;

    private:
        float DistanceToGround();
        float DistanceToWall(int direction);

        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int columnBegin;
        unsigned int columnEnd;
        int direction;
        sf::Vector2f velocity;
};
