#include "header.h"
#include "ui.h"

UI::UI()
{
    //ctor
}

UI::~UI()
{
    //dtor
}

void UI::CreateUI()
{
    marioText.setFont(pressStart2P);
    marioText.setString("MARIO");
    marioText.setCharacterSize(16);
    marioText.setFillColor(sf::Color::White);
    marioText.setOrigin(sf::Vector2f(marioText.getCharacterSize() * marioText.getString().getSize() / 2.0f, marioText.getCharacterSize() / 2.0f));

    scoreNumber.setFont(pressStart2P);
    scoreNumber.setCharacterSize(16);
    scoreNumber.setFillColor(sf::Color::White);

    coinIcons.push_back(CoinIcon());

    coinXText.setFont(pressStart2P);
    coinXText.setString("X");
    coinXText.setCharacterSize(16);
    coinXText.setFillColor(sf::Color::White);
    coinXText.setOrigin(sf::Vector2f(coinXText.getCharacterSize() * coinXText.getString().getSize() / 2.0f, coinXText.getCharacterSize() / 2.0f));

    coinNumber.setFont(pressStart2P);
    coinNumber.setCharacterSize(16);
    coinNumber.setFillColor(sf::Color::White);

    worldText.setFont(pressStart2P);
    worldText.setString("WORLD");
    worldText.setCharacterSize(16);
    worldText.setFillColor(sf::Color::White);
    worldText.setOrigin(sf::Vector2f(worldText.getCharacterSize() * worldText.getString().getSize() / 2.0f, worldText.getCharacterSize() / 2.0f));

    worldNumber.setFont(pressStart2P);
    worldNumber.setCharacterSize(16);
    worldNumber.setFillColor(sf::Color::White);

    timeText.setFont(pressStart2P);
    timeText.setString("TIME");
    timeText.setCharacterSize(16);
    timeText.setFillColor(sf::Color::White);
    timeText.setOrigin(sf::Vector2f(timeText.getCharacterSize() * timeText.getString().getSize() / 2.0f, timeText.getCharacterSize() / 2.0f));

    timeNumber.setFont(pressStart2P);
    timeNumber.setCharacterSize(16);
    timeNumber.setFillColor(sf::Color::White);

    livesIcon.setSize(sf::Vector2f(32.0f, 32.0f));
    livesIcon.setOrigin(livesIcon.getSize() / 2.0f);
    livesIcon.setTexture(&livesIconTexture);

    livesXText.setFont(pressStart2P);
    livesXText.setString("X");
    livesXText.setCharacterSize(16);
    livesXText.setFillColor(sf::Color::White);
    livesXText.setOrigin(sf::Vector2f(livesXText.getCharacterSize() * livesXText.getString().getSize() / 2.0f, livesXText.getCharacterSize() / 2.0f));

    livesNumber.setFont(pressStart2P);
    livesNumber.setCharacterSize(16);
    livesNumber.setFillColor(sf::Color::White);

    worldLoadingText.setFont(pressStart2P);
    worldLoadingText.setString("WORLD");
    worldLoadingText.setCharacterSize(16);
    worldLoadingText.setFillColor(sf::Color::White);
    worldLoadingText.setOrigin(sf::Vector2f(worldText.getCharacterSize() * worldText.getString().getSize() / 2.0f, worldText.getCharacterSize() / 2.0f));

    worldLoadingNumber.setFont(pressStart2P);
    worldLoadingNumber.setCharacterSize(16);
    worldLoadingNumber.setFillColor(sf::Color::White);

    gameOverText.setFont(pressStart2P);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(16);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOrigin(sf::Vector2f(gameOverText.getCharacterSize() * gameOverText.getString().getSize() / 2.0f, gameOverText.getCharacterSize() / 2.0f));
}

void UI::DrawUI(sf::RenderWindow& window, sf::Vector2f position, float deltaTime)
{
    ///Menu
    if (inGame == 0)
    {

    }
    ///Loading
    else if (inGame == 1)
    {
        marioText.setPosition(sf::Vector2f(position.x - 176.0f, position.y - 224.0f));
        window.draw(marioText);

        stringstream ss;
        ss << score;
        string scoreString = ss.str();

        if (score < 100000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 10000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 1000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 100)
        {
            scoreString.insert(0, "0");
        }
        if (score < 10)
        {
            scoreString.insert(0, "0");
        }

        scoreNumber.setString(scoreString);
        scoreNumber.setOrigin(sf::Vector2f(scoreNumber.getCharacterSize() * scoreNumber.getString().getSize() / 2.0f, scoreNumber.getCharacterSize() / 2.0f));
        scoreNumber.setPosition(sf::Vector2f(position.x - 168.0f, position.y - 208.0f));
        window.draw(scoreNumber);

        coinIcons[0].SetPosition(position.x - 84.0f, position.y - 212.0f);
        coinIcons[0].Update(deltaTime);
        coinIcons[0].Draw(window);

        coinXText.setPosition(sf::Vector2f(position.x - 64.0f, position.y - 208.0f));
        window.draw(coinXText);

        stringstream cs;
        cs << coinCounter;
        string coinString = cs.str();

        if (coinCounter < 10)
        {
            coinString.insert(0, "0");
        }

        coinNumber.setString(coinString);
        coinNumber.setOrigin(sf::Vector2f(coinNumber.getCharacterSize() * coinNumber.getString().getSize() / 2.0f, coinNumber.getCharacterSize() / 2.0f));
        coinNumber.setPosition(sf::Vector2f(position.x - 32.0f, position.y - 208.0f));
        window.draw(coinNumber);

        worldText.setPosition(sf::Vector2f(position.x + 64.0f, position.y - 224.0f));
        window.draw(worldText);

        stringstream ws;
        ws << level;
        string worldString = ws.str();
        worldString.insert(1, "-");

        worldNumber.setString(worldString);
        worldNumber.setOrigin(sf::Vector2f(worldNumber.getCharacterSize() * worldNumber.getString().getSize() / 2.0f, worldNumber.getCharacterSize() / 2.0f));
        worldNumber.setPosition(sf::Vector2f(position.x + 64.0f, position.y - 208.0f));
        window.draw(worldNumber);

        timeText.setPosition(sf::Vector2f(position.x + 176.0f, position.y - 224.0f));
        window.draw(timeText);

        ///Loading screen exclusive UI
        worldLoadingText.setPosition(sf::Vector2f(position.x - 48.0f, position.y - 64.0f));
        window.draw(worldLoadingText);

        stringstream wls;
        wls << level;
        string worldLoadingString = wls.str();
        worldLoadingString.insert(1, "-");

        worldLoadingNumber.setString(worldLoadingString);
        worldLoadingNumber.setOrigin(sf::Vector2f(worldLoadingNumber.getCharacterSize() * worldLoadingNumber.getString().getSize() / 2.0f, worldLoadingNumber.getCharacterSize() / 2.0f));
        worldLoadingNumber.setPosition(sf::Vector2f(position.x + 48.0f, position.y - 64.0f));
        window.draw(worldLoadingNumber);

        livesIcon.setPosition(sf::Vector2f(position.x - 48.0f, position.y - 4.0f));
        window.draw(livesIcon);

        livesXText.setPosition(sf::Vector2f(position.x - 0.0f, position.y - 0.0f));
        window.draw(livesXText);

        stringstream ls;
        ls << lives;
        string livesString = ls.str();

        livesNumber.setString(livesString);
        livesNumber.setOrigin(sf::Vector2f(livesNumber.getCharacterSize() * livesNumber.getString().getSize() / 2.0f, livesNumber.getCharacterSize() / 2.0f));
        livesNumber.setPosition(sf::Vector2f(position.x + 48.0f, position.y - 0.0f));
        window.draw(livesNumber);
    }
    ///Game
    else if (inGame == 2)
    {
        marioText.setPosition(sf::Vector2f(position.x - 176.0f, position.y - 224.0f));
        window.draw(marioText);

        stringstream ss;
        ss << score;
        string scoreString = ss.str();

        if (score < 100000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 10000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 1000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 100)
        {
            scoreString.insert(0, "0");
        }
        if (score < 10)
        {
            scoreString.insert(0, "0");
        }

        scoreNumber.setString(scoreString);
        scoreNumber.setOrigin(sf::Vector2f(scoreNumber.getCharacterSize() * scoreNumber.getString().getSize() / 2.0f, scoreNumber.getCharacterSize() / 2.0f));
        scoreNumber.setPosition(sf::Vector2f(position.x - 168.0f, position.y - 208.0f));
        window.draw(scoreNumber);

        coinIcons[0].SetPosition(position.x - 84.0f, position.y - 212.0f);
        coinIcons[0].Update(deltaTime);
        coinIcons[0].Draw(window);

        coinXText.setPosition(sf::Vector2f(position.x - 64.0f, position.y - 208.0f));
        window.draw(coinXText);

        stringstream cs;
        cs << coinCounter;
        string coinString = cs.str();

        if (coinCounter < 10)
        {
            coinString.insert(0, "0");
        }

        coinNumber.setString(coinString);
        coinNumber.setOrigin(sf::Vector2f(coinNumber.getCharacterSize() * coinNumber.getString().getSize() / 2.0f, coinNumber.getCharacterSize() / 2.0f));
        coinNumber.setPosition(sf::Vector2f(position.x - 32.0f, position.y - 208.0f));
        window.draw(coinNumber);

        worldText.setPosition(sf::Vector2f(position.x + 64.0f, position.y - 224.0f));
        window.draw(worldText);

        stringstream ws;
        ws << level;
        string worldString = ws.str();
        worldString.insert(1, "-");

        worldNumber.setString(worldString);
        worldNumber.setOrigin(sf::Vector2f(worldNumber.getCharacterSize() * worldNumber.getString().getSize() / 2.0f, worldNumber.getCharacterSize() / 2.0f));
        worldNumber.setPosition(sf::Vector2f(position.x + 64.0f, position.y - 208.0f));
        window.draw(worldNumber);

        timeText.setPosition(sf::Vector2f(position.x + 176.0f, position.y - 224.0f));
        window.draw(timeText);

        stringstream ts;
        ts << (int)(timeLimit + 0.5);
        string timeString = ts.str();

        timeNumber.setString(timeString);
        timeNumber.setOrigin(sf::Vector2f(timeNumber.getCharacterSize() * timeNumber.getString().getSize() / 2.0f, timeNumber.getCharacterSize() / 2.0f));
        timeNumber.setPosition(sf::Vector2f(position.x + 176.0f, position.y - 208.0f));
        window.draw(timeNumber);
    }
    ///Game over
    else if (inGame == 3)
    {
        marioText.setPosition(sf::Vector2f(position.x - 176.0f, position.y - 224.0f));
        window.draw(marioText);

        stringstream ss;
        ss << score;
        string scoreString = ss.str();

        if (score < 100000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 10000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 1000)
        {
            scoreString.insert(0, "0");
        }
        if (score < 100)
        {
            scoreString.insert(0, "0");
        }
        if (score < 10)
        {
            scoreString.insert(0, "0");
        }

        scoreNumber.setString(scoreString);
        scoreNumber.setOrigin(sf::Vector2f(scoreNumber.getCharacterSize() * scoreNumber.getString().getSize() / 2.0f, scoreNumber.getCharacterSize() / 2.0f));
        scoreNumber.setPosition(sf::Vector2f(position.x - 168.0f, position.y - 208.0f));
        window.draw(scoreNumber);

        coinIcons[0].SetPosition(position.x - 80.0f, position.y - 208.0f);
        coinIcons[0].Update(deltaTime);
        coinIcons[0].Draw(window);

        coinXText.setPosition(sf::Vector2f(position.x - 64.0f, position.y - 208.0f));
        window.draw(coinXText);

        stringstream cs;
        cs << coinCounter;
        string coinString = cs.str();

        if (coinCounter < 10)
        {
            coinString.insert(0, "0");
        }

        coinNumber.setString(coinString);
        coinNumber.setOrigin(sf::Vector2f(coinNumber.getCharacterSize() * coinNumber.getString().getSize() / 2.0f, coinNumber.getCharacterSize() / 2.0f));
        coinNumber.setPosition(sf::Vector2f(position.x - 32.0f, position.y - 208.0f));
        window.draw(coinNumber);

        worldText.setPosition(sf::Vector2f(position.x + 64.0f, position.y - 224.0f));
        window.draw(worldText);

        stringstream ws;
        ws << level;
        string worldString = ws.str();
        worldString.insert(1, "-");

        worldNumber.setString(worldString);
        worldNumber.setOrigin(sf::Vector2f(worldNumber.getCharacterSize() * worldNumber.getString().getSize() / 2.0f, worldNumber.getCharacterSize() / 2.0f));
        worldNumber.setPosition(sf::Vector2f(position.x + 64.0f, position.y - 208.0f));
        window.draw(worldNumber);

        timeText.setPosition(sf::Vector2f(position.x + 176.0f, position.y - 224.0f));
        window.draw(timeText);

        gameOverText.setPosition(position);
        window.draw(gameOverText);
    }
}
