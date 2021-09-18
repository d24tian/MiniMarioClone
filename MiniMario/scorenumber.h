#pragma once

#include <SFML/Graphics.hpp>

class ScoreNumber
{
    public:
        ScoreNumber(sf::Font* font, sf::Vector2f position, int number);
        ~ScoreNumber();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

        float scoreTimer;

    private:
        sf::Text body;
        sf::Vector2f position;
        int number;
};
