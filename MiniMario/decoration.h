#pragma once

#include <SFML/Graphics.hpp>

class Decoration
{
    public:
        Decoration(sf::Vector2f position, int type);
        ~Decoration();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);


    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int column;
        int type;
        /**
        0 = hillLeft
        1 = hillMiddleHolesRight
        2 = hillMiddleHolesLeft
        3 = hillMiddleEmpty
        4 = hillTop
        5 = hillRight

        6 = bushLeft
        7 = bushMiddle
        8 = bushRight

        9 = cloudLeft
        10 = cloudMiddle
        11 = cloudTop
        12 = cloudRight
        */
};
