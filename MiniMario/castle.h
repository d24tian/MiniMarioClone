#pragma once

#include <SFML/Graphics.hpp>

class Castle
{
    public:
        Castle(sf::Vector2f position);
        ~Castle();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        void DrawDoor(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return door.getPosition();}
        sf::Vector2f GetHalfSize() {return door.getSize() / 2.0f;}

        bool levelFinished;
        float finishTimer;

    private:
        sf::RectangleShape body;
        sf::RectangleShape door;
        sf::RectangleShape flag;
        int fireworksLaunched;
};
