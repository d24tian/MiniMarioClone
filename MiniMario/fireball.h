#pragma once

#include <SFML/Graphics.hpp>

class Fireball
{
    public:
        Fireball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int direction);
        ~Fireball();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        void Explode();

        bool exploded;

    private:
        float DistanceToGround();
        float DistanceToWall(int direction);

        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        int direction;
        sf::Vector2f velocity;
};
