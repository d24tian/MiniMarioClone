#pragma once

#include <SFML/Graphics.hpp>

class Goomba
{
    public:
        Goomba(sf::Texture* texture, sf::Vector2f position);
        ~Goomba();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        void Squish(int otherStreak);
        void Flip(int otherStreak);

        float squishTimer;
        bool isFlipping;

    private:
        float DistanceToGround ();
        float DistanceToWall (int direction);

        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        bool faceRight;
        int direction;
        sf::Vector2f velocity;
        sf::Vector2f startPos;
};
