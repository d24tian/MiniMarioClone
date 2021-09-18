#include "header.h"
#include "flagpole.h"

Flagpole::Flagpole(sf::Vector2f position)
{
    body.setSize(sf::Vector2f(4.0f, 288.0f));
    body.setOrigin(sf::Vector2f(body.getSize().x / 2.0f, body.getSize().y));
    body.setPosition(sf::Vector2f(position.x, position.y + 16.0f));
    top.setSize(sf::Vector2f(16.0f, 16.0f));
    top.setOrigin(top.getSize() / 2.0f);
    top.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y - body.getSize().y));
    flag.setSize(sf::Vector2f(32.0f, 32.0f));
    flag.setOrigin(flag.getSize() / 2.0f);
    flag.setPosition(sf::Vector2f(body.getPosition().x - (flag.getSize().x / 2.0f), body.getPosition().y - body.getSize().y + (flag.getSize().y / 2.0f)));
    this->grabbed = false;
    this->distance = 0.0f;
}

Flagpole::~Flagpole()
{
    //dtor
}

void Flagpole::SetSprite()
{
    body.setTexture(&flagpole);
    top.setTexture(&flagPoleTop);
    flag.setTexture(&flagpoleFlag);
    scoreText.setFont(pressStart2P);
}

void Flagpole::SetScoreText()
{
    distance = GetPercentage(players[0].GetPosition().y);
    if (distance <= 20.0f)
    {
        score += 5000;
        scoreText.setString("5000");
    }
    else if (distance <= 40.0f)
    {
        score += 2000;
        scoreText.setString("2000");
    }
    else if (distance <= 60.0f)
    {
        score += 800;
        scoreText.setString("800");
    }
    else if (distance <= 80.0f)
    {
        score += 400;
        scoreText.setString("400");
    }
    else if (distance <= 100.0f)
    {
        score += 100;
        scoreText.setString("100");
    }
    scoreText.setCharacterSize(12);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOrigin(sf::Vector2f(scoreText.getCharacterSize() * scoreText.getString().getSize() / 2.0f, scoreText.getCharacterSize() / 2.0f));
    scoreText.setPosition(sf::Vector2f(body.getPosition().x + 48.0f, players[0].GetPosition().y));
}

void Flagpole::Update(float deltaTime)
{
    ///Move the flag and update score
    if (grabbed)
    {
        ///Move score text
        if (scoreText.getPosition().y < body.getPosition().y)
        {
            scoreText.move(0.0f, -abs(distance / 100 * body.getSize().y * deltaTime));
        }

        ///Move flag
        if (flag.getPosition().y < body.getPosition().y - (flag.getSize().y / 2.0f))
        {
            flag.move(0.0f, (body.getSize().y - flag.getSize().y) * deltaTime);
        }
        else
        {
            requestedMusic = "courseClear";
        }

        ///Make sure the flag stays within bounds
        if (flag.getPosition().y < body.getPosition().y - body.getSize().y + (flag.getSize().y / 2.0f))
        {
            flag.setPosition(sf::Vector2f(flag.getPosition().x, body.getPosition().y - body.getSize().y + (flag.getSize().y / 2.0f)));
        }
        else if (flag.getPosition().y > body.getPosition().y - (flag.getSize().y / 2.0f))
        {
            flag.setPosition(sf::Vector2f(flag.getPosition().x, body.getPosition().y - (flag.getSize().y / 2.0f)));
        }

        ///Make sure the score text stays within bounds
        if (scoreText.getPosition().y < body.getPosition().y - body.getSize().y + (scoreText.getCharacterSize() / 2.0f))
        {
            scoreText.setPosition(sf::Vector2f(scoreText.getPosition().x, body.getPosition().y - body.getSize().y + (scoreText.getCharacterSize() / 2.0f)));
        }
        else if (scoreText.getPosition().y > body.getPosition().y - (scoreText.getCharacterSize() / 2.0f))
        {
            scoreText.setPosition(sf::Vector2f(scoreText.getPosition().x, body.getPosition().y - (scoreText.getCharacterSize() / 2.0f)));
        }
    }
}

///Custom draw to screen function
void Flagpole::Draw(sf::RenderWindow& window)
{
    window.draw(body);
    window.draw(top);
    window.draw(flag);
    window.draw(scoreText);
}
