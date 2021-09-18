#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        ~Animation();

        void Update(int row, int columnBegin, int columnEnd, float deltaTime, bool faceRight);
        void SetTexture(sf::Texture* texture);
        void SetSwitchtime(float switchTime) {this->switchTime = switchTime;};

        sf::IntRect uvRect;

    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;
        float totalTime;
        float switchTime;
};
