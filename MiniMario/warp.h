#pragma once

#include <SFML/Graphics.hpp>

class Warp
{
    public:
        Warp(sf::Vector2f position, int direction, int index);
        ~Warp();

        int GetWarp();
        void Update(float deltaTime);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

        /**
        0 = Inactive
        1 = Top
        2 = Bottom
        3 = Left
        4 = Right
        5 = Top Inactive
        6 = Bottom Inactive
        7 = Left Inactive
        8 = Right Inactive
        */
        int direction;
        int index;

    private:
        sf::RectangleShape body;
};
