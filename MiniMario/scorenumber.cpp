#include "header.h"
#include "scorenumber.h"

ScoreNumber::ScoreNumber(sf::Font* font, sf::Vector2f position, int number)
{
    body.setFont(*font);
    stringstream ns;
    ns << number;
    string numberString = ns.str();
    body.setString(numberString);
    body.setCharacterSize(12);
    body.setOrigin(sf::Vector2f(body.getCharacterSize() * body.getString().getSize() / 2.0f, body.getCharacterSize() / 2.0f));
    body.setPosition(position);
    this->position = position;
    this->number = number;
    this->scoreTimer = 100.0f;
}

ScoreNumber::~ScoreNumber()
{
    //dtor
}

void ScoreNumber::Update(float deltaTime)
{
    scoreTimer -= 100.0f * deltaTime;
    body.move(0.0f, -100.0f * deltaTime);
}

///Custom draw to screen function
void ScoreNumber::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
