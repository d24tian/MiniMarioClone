/**
WARNING: the code that follows will make you cry;
         a safety pig has been provided below for your benefit
                         _
 _._ _..._ .-',     _.._(`))
'-. `     '  /-._.-'    ',/
   )         \            '.
  / _    _    |             \
 |  a    a    /              |
 \   .-.                     ;
  '-('' ).-'       ,'       ;
     '-;           |      .'
        \           \    /
        | 7  .__  _.-\   \
        | |  |  ``/  /`  /
       /,_|  |   /,_/   /
          /,_/      '`-'

TO DO:

FINISH CROUCHING
Make menu
Make coin pickups able to be obtained by hitting the block below them
*/

#include "header.h"

///Constant variable to set the height of the player's view range in stone
static const float VIEW_HEIGHT = 480.0f;

///Vectors
vector<Player> players;
vector<Decoration> decorations;
vector<BreakableBlock> breakableBlocks;
vector<UnbreakableBlock> unbreakableBlocks;
vector<QuestionBlock> questionBlocks;
vector<Pipe> pipes;
vector<Warp> warps;
vector<Goomba> goombas;
vector<Koopa> koopas;
vector<CoinPickup> coinPickups;
vector<Flagpole> flagpoles;
vector<Castle> castles;
vector<Item> items;
vector<Fireball> fireballs;
vector<Explosion> explosions;
vector<Coin> coins;
vector<BlockParticle> blockParticles;
vector<CoinIcon> coinIcons;
vector<UI> uis;
vector<ScoreNumber> scoreNumbers;

///Audio manager
AudioManager audioManager;

///If this variable is false, the game will run normally, otherwise, all music and game functions will be paused
bool isPaused = false;

int inGame = 0;
float loadTimer = 3.0f;
int level = 11;
int area = 0;
int areaType = 0;

pause pauseCounter;

///UI variables
int lives = 3;
int score = 0;
int coinCounter = 0;
float timeLimit = 400.0f;

///Music changers
std::string requestedMusic = "";
std::string currentMusic = "";

///Resources
sf::Texture tilesheet;
sf::Texture blockParticle;
sf::Texture castle;
sf::Texture castleFlag;
sf::Texture castleDoor;
sf::Texture coin;
sf::Texture coinPickup;
sf::Texture explosion;
sf::Texture fireball;
sf::Texture flagpole;
sf::Texture flagPoleTop;
sf::Texture flagpoleFlag;
sf::Texture goomba;
sf::Texture item;
sf::Texture koopa;
sf::Texture livesIconTexture;
sf::Texture mario;

sf::Font pressStart2P;

///Manage the view window
void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

///MAIN----------------------------------------------------------------------------------------------------
int main()
{
    ///Create window
    sf::RenderWindow window(sf::VideoMode(512.0f, 480.0f), "MiniMario", sf::Style::Close | sf::Style::Titlebar);

    ///Create view
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512.0f, VIEW_HEIGHT));
    ResizeView(window, view);
    view.setCenter(sf::Vector2f(240.0f, 416.0f));

    ///Load resources
    tilesheet.loadFromFile("sprites/tilesheet.png");
    blockParticle.loadFromFile("sprites/blockParticle.png");
    castle.loadFromFile("sprites/castle.png");
    castleDoor.loadFromFile("sprites/castleDoor.png");
    castleFlag.loadFromFile("sprites/castleFlag.png");
    coin.loadFromFile("sprites/coin.png");
    coinPickup.loadFromFile("sprites/coinPickup.png");
    explosion.loadFromFile("sprites/explosion.png");
    fireball.loadFromFile("sprites/fireball.png");
    flagpole.loadFromFile("sprites/flagpole.png");
    flagPoleTop.loadFromFile("sprites/flagPoleTop.png");
    flagpoleFlag.loadFromFile("sprites/flagPoleFlag.png");
    goomba.loadFromFile("sprites/goomba.png");
    item.loadFromFile("sprites/item.png");
    koopa.loadFromFile("sprites/koopa.png");
    livesIconTexture.loadFromFile("sprites/livesIcon.png");
    mario.loadFromFile("sprites/mario.png");

    pressStart2P.loadFromFile("fonts/pressStart2P.ttf");

    ///Load audio
    audioManager.LoadAudio();
    audioManager.Add("audio/nothing.wav", false);
    audioManager.Add("audio/courseClear.wav", false);
    audioManager.Add("audio/death.wav", false);
    audioManager.Add("audio/gameOver.wav", false);
    audioManager.Add("audio/invincible.wav", true);
    audioManager.Add("audio/invincibleHurryUp.wav", true);
    audioManager.Add("audio/overworld.wav", true);
    audioManager.Add("audio/overworldHurryUp.wav", true);
    audioManager.Add("audio/underground.wav", true);
    audioManager.Add("audio/undergroundhurryUp.wav", true);
    audioManager.Add("audio/warning.wav", false);
    audioManager.SetCurrent(0);

    ///Create UI
    uis.push_back(UI());
    uis[0].CreateUI();

    ///Create player class
    players.push_back(Player(&mario, sf::Vector2u(22, 22), 0.075f, 5.0f, 981.0f));

    ///Start deltaTime
    float deltaTime = 0.0f;
    sf::Clock clock;

    ///MAIN GAME LOOP----------------------------------------------------------------------------------------------------
    while (window.isOpen())
    {
        ///Handle window events, such as closing the window, leaving the window, coming back to the window after leaving it, etc.
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            ///Check whether or not the player currently has focus on the game window
            case sf::Event::GainedFocus:
                audioManager.GetCurrent()->play();
                deltaTime = clock.restart().asSeconds();
                isPaused = false;
                break;
            case sf::Event::LostFocus:
                audioManager.GetCurrent()->pause();
                audioManager.PlayAudio("pause");
                isPaused = true;
                break;
            }
        }

        ///Game functions if the game if not paused
        if (!isPaused)
        {
            ///Restart deltaTime at the beginning of each frame
            deltaTime = clock.restart().asSeconds();

            ///Manage music
            ///Make sure that if the requested music is already playing as the current music, then we do not restart the music
            if (requestedMusic != currentMusic)
            {
                ///Stop the previous track
                if (audioManager.GetCurrent()->getStatus() == sf::SoundSource::Playing)
                {
                    audioManager.GetCurrent()->stop();
                }

                ///Set the new track
                if (requestedMusic == "")
                {
                    audioManager.SetCurrent(0);
                }
                else if (requestedMusic == "courseClear")
                {
                    audioManager.SetCurrent(1);
                }
                else if (requestedMusic == "death")
                {
                    audioManager.SetCurrent(2);
                }
                else if (requestedMusic == "gameOver")
                {
                    audioManager.SetCurrent(3);
                }
                else if (requestedMusic == "invincible")
                {
                    audioManager.SetCurrent(4);
                }
                else if (requestedMusic == "invincibleHurryUp")
                {
                    audioManager.SetCurrent(5);
                }
                else if (requestedMusic == "overworld")
                {
                    audioManager.SetCurrent(6);
                }
                else if (requestedMusic == "overworldHurryUp")
                {
                    audioManager.SetCurrent(7);
                }
                else if (requestedMusic == "underground")
                {
                    audioManager.SetCurrent(8);
                }
                else if (requestedMusic == "undergroundHurryUp")
                {
                    audioManager.SetCurrent(9);
                }
                else if (requestedMusic == "warning")
                {
                    audioManager.SetCurrent(10);
                }
                ///Play the new track
                audioManager.GetCurrent()->play();
                currentMusic = requestedMusic;
            }

            ///Menu
            ///UNFINISHED
            if (inGame == 0)
            {
                loadTimer = 3.0f;
                inGame = 1;
            }
            ///Loading screen
            else if (inGame == 1)
            {
                ///Draw screen at least once
                ///Reset view
                view.setCenter(sf::Vector2f(0.0f, 0.0f));

                ///Reset window
                window.clear(sf::Color(0, 0, 0));
                window.setView(view);

                ///Update and draw text
                uis[0].DrawUI(window, view.getCenter(), deltaTime);
                coinIcons[0].Draw(window);

                ///Display everything that is drawn to the window
                window.display();

                ///Set music
                requestedMusic = "";

                ///Do timer
                if (loadTimer == 3.0f)
                {
                    ///Start level
                    StartLevel(level);
                    loadTimer -= deltaTime;
                }
                ///If after the level loads successfully, 3 seconds have not yet passed
                else if (loadTimer > 0.0f)
                {
                    loadTimer -= deltaTime;
                }
                ///After 3 seconds have passed and the level has started, we change to the game itself
                else if (loadTimer <= 0.0f)
                {
                    loadTimer = 0.0f;
                    inGame = 2;

                    ///Update music
                    if (level == 11)
                    {
                        requestedMusic = "overworld";
                    }
                }
            }
            ///Game
            else if (inGame == 2)
            {
                ///Update music
                ///If the player is running low on time, play a warning sound
                if ((int)(timeLimit + 0.5) == 100)
                {
                    if (currentMusic == "overworld" || currentMusic == "underground" || currentMusic == "invincible")
                    {
                        requestedMusic = "warning";
                    }
                }

                ///After the warning sound ends, play the sped up version of the regular music
                if (currentMusic == "warning" && audioManager.GetCurrent()->getStatus() == sf::SoundSource::Stopped)
                {
                    if (players[0].invincibilityTimer != -1.0f)
                    {
                        requestedMusic = "invincibleHurryUp";
                    }
                    else if (level == 11)
                    {
                        if (area == 0)
                        {
                            requestedMusic = "overworldHurryUp";
                        }
                        else if (area == 1)
                        {
                            requestedMusic = "undergroundHurryUp";
                        }
                    }
                }

                ///Update areaType
                if (level == 11)
                {
                    if (area == 0)
                    {
                        areaType = 0;
                    }
                    else if (area == 1)
                    {
                        areaType = 1;
                    }
                }
                else if (level == 12)
                {

                }

                ///Update the player
                players[0].Update(deltaTime);

                ///Set the view to be focused on the player only on the x axis
                if (level == 11)
                {
                    if (area == 0)
                    {
                        if (players[0].GetPosition().x < 240.0f)
                        {
                            view.setCenter(sf::Vector2f(240.0f, 416.0f));
                        }
                        else if (players[0].GetPosition().x > 6384.0f)
                        {
                            view.setCenter(sf::Vector2f(6384.0f, 416.0f));
                        }
                        else
                        {
                            view.setCenter(sf::Vector2f(players[0].GetPosition().x, 416.0f));
                        }
                    }
                    ///If the player is in the pipe area in stage 1-1, the camera will be locked into this position
                    else if (area == 1)
                    {
                        view.setCenter(sf::Vector2f(6896.0f, 416.0f));
                    }
                }
                ///For unimplemented levels
                else
                {
                    view.setCenter(sf::Vector2f(players[0].GetPosition().x, 416.0f));
                }

                ///Refresh window
                if (level == 11)
                {
                    ///If the player is in the overworld, set the background colour to sky blue
                    if (area == 0)
                    {
                        window.clear(sf::Color(92, 148, 252));
                    }
                    ///If the player is in the cave, set the background colour to be pitch black
                    else if (area == 1)
                    {
                        window.clear(sf::Color(0, 0, 0));
                    }
                }
                ///For unimplemented levels
                else
                {
                    window.clear(sf::Color(92, 148, 252));
                }
                ///Self explanatory
                window.setView(view);

                ///Update and draw, and delete all classes when necessary
                ///The order of the drawing matters, since whatever is drawn last will be displayed on top
                for (int i = 0; i < decorations.size(); i++)
                {
                    decorations[i].Update(deltaTime);
                    decorations[i].Draw(window);
                }

                for (int i = 0; i < items.size(); i++)
                {
                    items[i].Update(deltaTime);
                    items[i].Draw(window);
                }

                for (int i = 0; i < flagpoles.size(); i++)
                {
                    flagpoles[i].Update(deltaTime);
                    flagpoles[i].Draw(window);
                }

                for (int i = 0; i < castles.size(); i++)
                {
                    castles[i].Update(deltaTime);
                    castles[i].Draw(window);
                    castles[i].DrawDoor(window);
                }

                players[0].Draw(window);

                for (int i = 0; i < breakableBlocks.size(); i++)
                {
                    breakableBlocks[i].Update(deltaTime);
                    breakableBlocks[i].Draw(window);
                    if (breakableBlocks[i].isBroken)
                    {
                        breakableBlocks.erase(breakableBlocks.begin() + i);
                    }
                }

                for (int i = 0; i < unbreakableBlocks.size(); i++)
                {
                    unbreakableBlocks[i].Update(deltaTime);
                    unbreakableBlocks[i].Draw(window);
                }

                for (int i = 0; i < questionBlocks.size(); i++)
                {
                    questionBlocks[i].Update(deltaTime);
                    questionBlocks[i].Draw(window);
                }

                for (int i = 0; i < pipes.size(); i++)
                {
                    pipes[i].Update(deltaTime);
                    pipes[i].Draw(window);
                }

                for (int i = 0; i < coinPickups.size(); i++)
                {
                    coinPickups[i].Update(deltaTime);
                    coinPickups[i].Draw(window);
                }

                for (int i = 0; i < coins.size(); i++)
                {
                    coins[i].Update(deltaTime);
                    coins[i].Draw(window);
                    if (coins[i].movement == 2)
                    {
                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, coins[i].GetPosition(), 200));
                        coins.erase(coins.begin() + i);
                    }
                }

                ///If the item has fully arisen out of its block, then we will draw the item over blocks
                for (int i = 0; i < items.size(); i++)
                {
                    if (items[i].spawnTimer <= 0.0f)
                    {
                        items[i].Draw(window);
                    }
                }

                for (int i = 0; i < goombas.size(); i++)
                {
                    goombas[i].Update(deltaTime);
                    goombas[i].Draw(window);
                    if (goombas[i].squishTimer >= 1.5f)
                    {
                        goombas.erase(goombas.begin() + i);
                    }
                }

                for (int i = 0; i < koopas.size(); i++)
                {
                    koopas[i].Update(deltaTime);
                    koopas[i].Draw(window);
                }

                for (int i = 0; i < fireballs.size(); i++)
                {
                    fireballs[i].Update(deltaTime);
                    fireballs[i].Draw(window);
                    if (fireballs[i].exploded == true)
                    {
                        fireballs.erase(fireballs.begin() + i);
                    }
                }

                for (int i = 0; i < explosions.size(); i++)
                {
                    explosions[i].Update(deltaTime);
                    explosions[i].Draw(window);
                    if (explosions[i].explosionTimer >= 0.6f)
                    {
                        explosions.erase(explosions.begin() + i);
                    }
                }

                for (int i = 0; i < blockParticles.size(); i++)
                {
                    blockParticles[i].Update(deltaTime);
                    blockParticles[i].Draw(window);
                    if (blockParticles[i].isOutside)
                    {
                        blockParticles.erase(blockParticles.begin() + i);
                    }
                }

                for (int i = 0; i < scoreNumbers.size(); i++)
                {
                    scoreNumbers[i].Update(deltaTime);
                    scoreNumbers[i].Draw(window);
                    if (scoreNumbers[i].scoreTimer <= 0.0f)
                    {
                        scoreNumbers.erase(scoreNumbers.begin() + i);
                    }
                }

                ///As long as we don'd need the player to be behind a warp pipe during the warp animation, the player will be drawn on top of all non-UI objects
                if (players[0].isWarping == 0)
                {
                    players[0].Draw(window);
                }

                ///Update and draw UI
                uis[0].DrawUI(window, view.getCenter(), deltaTime);

                ///Pauses for picking up a power up or taking damage
                if (pauseCounter.switchTimer != -1.0f)
                {
                    ///Set the original position of the animation
                    if (pauseCounter.before< pauseCounter.after && pauseCounter.before == 0)
                    {
                        pauseCounter.position = sf::Vector2f(players[0].GetPosition().x, players[0].GetPosition().y - 16.0f);
                    }
                    else
                    {
                        pauseCounter.position = players[0].GetPosition();
                    }

                    ///Play animations
                    ///Before looking over this, I advise you to take a look at the player's sprite sheet in the sprites folder ("sprites/mario.png")
                    while (pauseCounter.switchTimer > 0.0f)
                    {
                        ///Restart timer at the beginning of each frame
                        deltaTime = clock.restart().asSeconds();
                        ///Picking up items
                        ///Small to big
                        if (pauseCounter.before == 0 && pauseCounter.after == 1)
                        {
                            players[0].SetSpritePosition(pauseCounter.position);
                            ///Enlarged head
                            if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 0)
                            {
                                players[0].SetRow(1, deltaTime);
                                players[0].SetColumn(16, 16, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                            ///Big
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 2)
                            {
                                players[0].SetRow(1, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                            ///Small
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 1)
                            {
                                players[0].SetRow(0, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 32.0f));
                            }
                        }
                        ///Small to fire
                        else if (pauseCounter.before == 0 && pauseCounter.after == 2)
                        {
                            players[0].SetSpritePosition(pauseCounter.position);
                            ///Enlarged head
                            if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 0)
                            {
                                players[0].SetRow(5, deltaTime);
                                players[0].SetColumn(16, 16, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                            ///Fire
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 2)
                            {
                                players[0].SetRow(5, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                            ///Small
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 1)
                            {
                                players[0].SetRow(0, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 32.0f));
                            }
                        }
                        ///Big to fire
                        else if (pauseCounter.before == 1 && pauseCounter.after == 2)
                        {
                            players[0].SetSpritePosition(pauseCounter.position);
                            ///Fire
                            if ((int)((pauseCounter.switchTimer * 6) + 0.5) % 2 == 0)
                            {
                                players[0].SetRow(5, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                            ///Big
                            else if ((int)((pauseCounter.switchTimer * 6) + 0.5) % 2 == 1)
                            {
                                players[0].SetRow(1, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                        }
                        ///Hurt
                        ///Fire to small
                        else if (pauseCounter.before == 2 && pauseCounter.after == 0)
                        {
                            players[0].SetSpritePosition(pauseCounter.position);
                            ///Enlarged head
                            if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 0)
                            {
                                players[0].SetRow(5, deltaTime);
                                players[0].SetColumn(16, 16, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                            ///Small
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 2)
                            {
                                players[0].SetRow(0, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 32.0f));
                            }
                            ///Fire
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 1)
                            {
                                players[0].SetRow(5, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                        }
                        ///Big to small
                        else if (pauseCounter.before == 1 && pauseCounter.after == 0)
                        {
                            players[0].SetSpritePosition(pauseCounter.position);
                            ///Enlarged head
                            if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 0)
                            {
                                players[0].SetRow(1, deltaTime);
                                players[0].SetColumn(16, 16, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                            ///Small
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 2)
                            {
                                players[0].SetRow(0, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 32.0f));
                            }
                            ///Big
                            else if ((int)((pauseCounter.switchTimer * 9) + 0.5) % 3 == 1)
                            {
                                players[0].SetRow(1, deltaTime);
                                players[0].SetColumn(0, 0, deltaTime);
                                players[0].SetSize(sf::Vector2f(24.0f, 64.0f));
                            }
                        }

                        ///Draw player and window
                        if (level == 11)
                        {
                            if (area == 0)
                            {
                                if (players[0].GetPosition().x < 240.0f)
                                {
                                    view.setCenter(sf::Vector2f(240.0f, 416.0f));
                                }
                                else if (players[0].GetPosition().x > 6384.0f)
                                {
                                    view.setCenter(sf::Vector2f(6384.0f, 416.0f));
                                }
                                else
                                {
                                    view.setCenter(sf::Vector2f(players[0].GetPosition().x, 416.0f));
                                }
                            }
                            else if (area == 1)
                            {
                                view.setCenter(sf::Vector2f(6992.0f, 416.0f));
                            }
                        }
                        else
                        {
                            view.setCenter(sf::Vector2f(players[0].GetPosition().x, 416.0f));
                        }
                        ///Refresh window
                        if (level == 11)
                        {
                            if (area == 0)
                            {
                                window.clear(sf::Color(92, 148, 252));
                            }
                            else if (area == 1)
                            {
                                window.clear(sf::Color(0, 0, 0));
                            }
                        }
                        else
                        {
                            window.clear(sf::Color(92, 148, 252));
                        }
                        ///Set view
                        window.setView(view);

                        ///Draw all other objects
                        for (int i = 0; i < decorations.size(); i++)
                        {
                            decorations[i].Draw(window);
                        }
                        for (int i = 0; i < items.size(); i++)
                        {
                            items[i].Draw(window);
                        }
                        for (int i = 0; i < coins.size(); i++)
                        {
                            coins[i].Draw(window);
                        }
                        for (int i = 0; i < flagpoles.size(); i++)
                        {
                            flagpoles[i].Draw(window);
                        }
                        for (int i = 0; i < castles.size(); i++)
                        {
                            castles[i].Draw(window);
                            castles[i].DrawDoor(window);
                        }
                        players[0].Draw(window);
                        for (int i = 0; i < breakableBlocks.size(); i++)
                        {
                            breakableBlocks[i].Draw(window);
                        }
                        for (int i = 0; i < unbreakableBlocks.size(); i++)
                        {
                            unbreakableBlocks[i].Draw(window);
                        }
                        for (int i = 0; i < questionBlocks.size(); i++)
                        {
                            questionBlocks[i].Draw(window);
                        }
                        for (int i = 0; i < pipes.size(); i++)
                        {
                            pipes[i].Draw(window);
                        }
                        for (int i = 0; i < coinPickups.size(); i++)
                        {
                            coinPickups[i].Draw(window);
                        }
                        for (int i = 0; i < items.size(); i++)
                        {
                            if (items[i].spawnTimer <= 0.0f)
                            {
                                items[i].Draw(window);
                            }
                        }
                        for (int i = 0; i < goombas.size(); i++)
                        {
                            goombas[i].Draw(window);
                        }
                        for (int i = 0; i < koopas.size(); i++)
                        {
                            koopas[i].Draw(window);
                        }
                        for (int i = 0; i < fireballs.size(); i++)
                        {
                            fireballs[i].Draw(window);
                        }
                        for (int i = 0; i < explosions.size(); i++)
                        {
                            explosions[i].Draw(window);
                        }
                        for (int i = 0; i < blockParticles.size(); i++)
                        {
                            blockParticles[i].Update(deltaTime);
                            blockParticles[i].Draw(window);
                            if (blockParticles[i].isOutside)
                            {
                                blockParticles.erase(blockParticles.begin() + i);
                            }
                        }
                        for (int i = 0; i < scoreNumbers.size(); i++)
                        {
                            scoreNumbers[i].Update(deltaTime);
                            scoreNumbers[i].Draw(window);
                            if (scoreNumbers[i].scoreTimer <= 0.0f)
                            {
                                scoreNumbers.erase(scoreNumbers.begin() + i);
                            }
                        }
                        if (players[0].isWarping == 0)
                        {
                            players[0].Draw(window);
                        }
                        uis[0].DrawUI(window, view.getCenter(), deltaTime);
                        ///Display window
                        window.display();

                        ///Deduct the amount of time each frame took from the total animation time
                        pauseCounter.switchTimer -= deltaTime;
                    }

                    ///Reset the animation timer to avoid bugs
                    pauseCounter.switchTimer = -1.0f;

                    ///If player took damage, apply temporary invincibility
                    if (pauseCounter.before > pauseCounter.after)
                    {
                        players[0].graceTimer = 1.0f;
                    }

                    ///Manager player's position for a smoother finish to the animation
                    if (pauseCounter.before == 0 && pauseCounter.before < pauseCounter.after)
                    {
                        players[0].Move(sf::Vector2f(0.0f, -16.0f));
                    }
                }

                ///Display the window
                window.display();

                ///Decrease the amount of time the player has left based on deltaTime
                if (timeLimit > 0.0f && players[0].isGrabbing == 0)
                {
                    timeLimit -= deltaTime;
                }
                ///Don't decrease time if the player has already finished the level
                else if (players[0].isGrabbing == 0)
                {
                    timeLimit = 0.0f;
                    if (players[0].isBig > -1)
                    {
                        players[0].Hurt(1);
                    }
                }
            }
            ///Game over screen
            else if (inGame == 3)
            {
                ///Set music
                requestedMusic = "gameOver";

                ///Do timer
                if (loadTimer > 0.0f)
                {
                    loadTimer -= deltaTime;
                }
                else
                {
                    ///Reset lives and go back to menu
                    lives = 3;
                    inGame = 0;
                }

                ///All the regular stuff
                ///Reset view
                view.setCenter(sf::Vector2f(0.0f, 0.0f));

                window.clear(sf::Color(0, 0, 0));
                window.setView(view);

                ///Update and draw text
                uis[0].DrawUI(window, view.getCenter(), deltaTime);

                window.display();
            }
        }
        ///Game functions when the player does not have focus on the screen/has paused the game
        else if (isPaused)
        {

        }
    }

    ///lol This will never be triggered
    return 0;
}
