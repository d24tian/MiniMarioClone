#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class UI
{
    public:
        UI();
        ~UI();

        void CreateUI();
        void DrawUI(sf::RenderWindow& window, sf::Vector2f position, float deltaTime);

    private:
        sf::Text marioText;
        sf::Text scoreNumber;
        sf::Text coinXText;
        sf::Text coinNumber;
        sf::Text worldText;
        sf::Text worldNumber;
        sf::Text timeText;
        sf::Text timeNumber;
        sf::RectangleShape livesIcon;
        sf::Text livesXText;
        sf::Text livesNumber;
        sf::Text worldLoadingText;
        sf::Text worldLoadingNumber;
        sf::Text gameOverText;

};
