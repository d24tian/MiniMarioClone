#include "header.h"

void StartLevel(int index)
{
    ///Clear vectors
	decorations.clear();
	breakableBlocks.clear();
	unbreakableBlocks.clear();
	questionBlocks.clear();
	pipes.clear();
	warps.clear();
	goombas.clear();
	koopas.clear();
	coinPickups.clear();
	flagpoles.clear();
	castles.clear();
    items.clear();
    fireballs.clear();
    explosions.clear();
    coins.clear();
    scoreNumbers.clear();

    ///Create blocks
	blockPoint tmpAdd;

    string line = "";
    int paramCounter = 0;

    string currentParam = "";
    int intParam = 0;

	///Open file
	std::string currentLevel = "";
	if (level == 11)
    {
        currentLevel = "levels/11.txt";
    }
	else if (level == 12)
    {
        currentLevel = "levels/12.txt";
    }
    ifstream levelFile(currentLevel);

    ///Read file
    if (levelFile.is_open())
    {
        ///Loop through each line in the text file
        while (getline(levelFile, line))
        {
            ///Loop through each character of the current line being scanned
            for (int i = 0; i < line.size(); i++)
            {
                ///Check for comments
                if (line[0] == '/' && line[1] == '/')
                {
                    break;
                }
                ///If the current character being scanned is a number, add it to the currentParam variable
                else if (line[i] != ' ' && line[i] != ';')
                {
                    currentParam += line[i];
                }
                ///If it is not, then apply the last currentParam
                else
                {
                    if (paramCounter == 0)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.index = intParam;
                    }
                    else if (paramCounter == 1)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.x = intParam;
                    }
                    else if (paramCounter == 2)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.y = intParam;
                    }
                    else if (paramCounter == 3)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.type = intParam;
                    }
                    else if (paramCounter == 4)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.param = intParam;
                    }
                    ///Reset for next loop
                    currentParam = "";
                    paramCounter++;
                }
            }

            ///Create blocks based on parameters
            if (tmpAdd.index == -1)
            {
                decorations.push_back(Decoration(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f), tmpAdd.type));
            }
            else if (tmpAdd.index == 0)
            {
                breakableBlocks.push_back(BreakableBlock(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f), tmpAdd.type, tmpAdd.param));
            }
            else if (tmpAdd.index == 1)
            {
                unbreakableBlocks.push_back(UnbreakableBlock(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f), tmpAdd.type));
            }
            else if (tmpAdd.index == 2)
            {
                questionBlocks.push_back(QuestionBlock(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f), tmpAdd.type, tmpAdd.param));
            }
            else if (tmpAdd.index == 3)
            {
                pipes.push_back(Pipe(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f), tmpAdd.type));
            }
            else if (tmpAdd.index == 4)
            {
                warps.push_back(Warp(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f), tmpAdd.type, tmpAdd.param));
            }
            else if (tmpAdd.index == 5)
            {
                goombas.push_back(Goomba(&goomba, sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f)));
            }
            else if (tmpAdd.index == 6)
            {
                koopas.push_back(Koopa(&koopa, sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f)));
            }
            else if (tmpAdd.index == 7)
            {
                coinPickups.push_back(CoinPickup(&coinPickup, sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f)));
            }
            else if (tmpAdd.index == 8)
            {
                flagpoles.push_back(Flagpole(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f)));
            }
            else if (tmpAdd.index == 9)
            {
                castles.push_back(Castle(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f)));
            }
            ///Reset for next loop
            paramCounter = 0;
            tmpAdd.index = -1;
            tmpAdd.x = -1;
            tmpAdd.y = -1;
            tmpAdd.type = -1;
            tmpAdd.param = -1;
        }
        ///Close the file when finished
        levelFile.close();
    }
    else
    {
        ///Hopefully this will never happen
        std::cout << "Unable to open file";
    }

    ///Set area to default
    area = 0;

    ///Update music
    if (level == 11)
    {
        requestedMusic = "overworld";
    }

    ///Reset player
    players[0].Reset();

    ///Start timer
    timeLimit = 400.0f;

    ///Do other functions
    SetTextures();
}

///Set the sprites of all classes that needs it
void SetTextures()
{
    for (int i = 0; i < decorations.size(); i++)
    {
        decorations[i].SetSprite();
    }

    for (int i = 0; i < breakableBlocks.size(); i++)
    {
        breakableBlocks[i].SetSprite();
    }

    for (int i = 0; i < unbreakableBlocks.size(); i++)
    {
        unbreakableBlocks[i].SetSprite();
    }

    for (int i = 0; i < questionBlocks.size(); i++)
    {
        questionBlocks[i].SetSprite();
    }

    for (int i = 0; i < pipes.size(); i++)
    {
        pipes[i].SetSprite();
    }

    for (int i = 0; i < goombas.size(); i++)
    {
        goombas[i].SetSprite();
    }

    for (int i = 0; i < koopas.size(); i++)
    {
        koopas[i].SetSprite();
    }

    for (int i = 0; i < coinPickups.size(); i++)
    {
        coinPickups[i].SetSprite();
    }

    for (int i = 0; i < flagpoles.size(); i++)
    {
        flagpoles[i].SetSprite();
    }

    for (int i = 0; i < castles.size(); i++)
    {
        castles[i].SetSprite();
    }
}

///Function to determine how much score the player should be rewarded for defeating an enemy based on their current streak
int GetStreakScore(int streak)
{
    int streakScore;
    if (streak == 1)
    {
        streakScore = 100;
    }
    else if (streak == 2)
    {
        streakScore = 200;
    }
    else if (streak == 3)
    {
        streakScore = 400;
    }
    else if (streak == 4)
    {
        streakScore = 500;
    }
    else if (streak == 5)
    {
        streakScore = 800;
    }
    else if (streak == 6)
    {
        streakScore = 1000;
    }
    else if (streak == 7)
    {
        streakScore = 2000;
    }
    else if (streak == 8)
    {
        streakScore = 4000;
    }
    else if (streak == 9)
    {
        streakScore = 5000;
    }
    else if (streak == 10)
    {
        streakScore = 8000;
    }
    else if (streak > 10)
    {
        streakScore = 0;
    }
    return streakScore;
}
