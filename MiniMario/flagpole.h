#pragma once

#include <SFML/Graphics.hpp>

class Flagpole
{
    public:
        Flagpole(sf::Vector2f position);
        ~Flagpole();

        void SetSprite();
        void SetScoreText();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        float GetPercentage(float position) {return ((position - top.getPosition().y) / (body.getPosition().y - top.getPosition().y)) * 100;}

        bool grabbed;

    private:
        sf::RectangleShape body;
        sf::RectangleShape top;
        sf::RectangleShape flag;
        sf::Text scoreText;
        float distance;
};
