#pragma once

#include <SFML/Graphics.hpp>

class Explosion
{
    public:
        Explosion(sf::Texture* texture, sf::Vector2f position);
        ~Explosion();

        void SetSprite();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

        float explosionTimer;

    private:
        sf::RectangleShape body;
        Animation animation;
};
