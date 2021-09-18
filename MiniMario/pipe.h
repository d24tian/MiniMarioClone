#pragma once

#include <SFML/Graphics.hpp>

class Pipe
{
    public:
        Pipe(sf::Vector2f position, int type);
        ~Pipe();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int column;
        bool faceLeft;
        int type;
        /**
        0 = topLeft
        1 = topRight
        2 = shaftLeft
        3 = shaftRight
        4 = leftTopTop
        5 = leftTopBottom
        6 = leftShaftTop
        7 = leftShaftBottom
        8 = leftConnectTop
        9 = leftConnectBottom
        10 = rightTopTop
        11 = rightTopBottom
        12 = rightShaftTop
        13 = rightShaftBottom
        14 = rightConnectTop
        15 = rightConnectBottom
        */
};
