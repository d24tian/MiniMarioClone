#include "header.h"
#include "explosion.h"

Explosion::Explosion(sf::Texture* texture, sf::Vector2f position) :
    animation(texture, sf::Vector2u(3, 1), 0.2f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
    this->explosionTimer = 0.0f;

    audioManager.PlayAudio("fireworks");
}

Explosion::~Explosion()
{
    //dtor
}

///Set sprite based on type
void Explosion::SetSprite()
{
    animation.SetTexture(&explosion);
    body.setTexture(&explosion);
}

void Explosion::Update(float deltaTime)
{
    ///Update animations
    body.setTexture(&explosion);
    animation.Update(0, 0, 2, deltaTime, true);
    body.setTextureRect(animation.uvRect);

    explosionTimer += deltaTime;
}

///Custom draw to screen function
void Explosion::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
