#pragma once

#include <SFML/Graphics.hpp>

class Koopa
{
    public:
        Koopa(sf::Texture* texture, sf::Vector2f position);
        ~Koopa();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        void Squish(int otherStreak);
        void Flip(int otherStreak);

        int state; ///0 = Normal, 1 = Stationary shell, 2 = Moving shell
        bool isFlipping;
        int direction;
        int streak;

    private:
        float DistanceToGround ();
        float DistanceToWall (int direction);

        sf::RectangleShape body;
        sf::RectangleShape sprite;
        Animation animation;
        unsigned int row;
        bool faceRight;
        sf::Vector2f velocity;
        sf::Vector2f startPos;
};
