#pragma once

#include "animation.h"
#include <SFML/Graphics.hpp>

class QuestionBlock
{
    public:
        QuestionBlock(sf::Vector2f position, int type, int param);
        ~QuestionBlock();

        void SetSprite();
        void Update(float deltaTime);
        void OnCollision(int isBig);
        void Draw(sf::RenderWindow& window);
        int GetType() {return type;}
        int GetParam() {return param;}
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

    private:
        int GetItem();
        int GetGoomba();
        int GetKoopa();

        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int columnBegin;
        unsigned int columnEnd;
        int type;
        int param;
        float collideCounter;
        float originalY;
};
