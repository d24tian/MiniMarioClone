#pragma once

///Include ABSOLUTELY EVERYTHING
#include "animation.h"
#include "audiomanager.h"
#include "blockparticle.h"
#include "breakableblock.h"
#include "castle.h"
#include "coin.h"
#include "coinicon.h"
#include "coinpickup.h"
#include "decoration.h"
#include "explosion.h"
#include "fireball.h"
#include "flagpole.h"
#include "goomba.h"
#include "item.h"
#include "koopa.h"
#include "pipe.h"
#include "player.h"
#include "questionblock.h"
#include "scorenumber.h"
#include "ui.h"
#include "unbreakableblock.h"
#include "warp.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

///Because why not
using namespace std;

///Variable for appending blocks from level files into the game
struct blockPoint
{
    int index;
	int x;
	int y;
	int type;
	int param;
};

///Structure variable used by the player class when detecting blocks above the player
struct blockType
{
    int index;
    int location;
    int type;
    int param;
};

///Used to play the player animation for powering up/taking damage
struct pause
{
    float switchTimer;
    int before;
    int after;
    sf::Vector2f position;
};

///Game functions
void StartLevel(int index);
void SetTextures();
int GetStreakScore(int streak);

///Global vectors
extern vector<Player> players;
extern vector<Decoration> decorations;
extern vector<BreakableBlock> breakableBlocks;
extern vector<UnbreakableBlock> unbreakableBlocks;
extern vector<QuestionBlock> questionBlocks;
extern vector<Pipe> pipes;
extern vector<Warp> warps;
extern vector<Goomba> goombas;
extern vector<Koopa> koopas;
extern vector<CoinPickup> coinPickups;
extern vector<Flagpole> flagpoles;
extern vector<Castle> castles;
extern vector<Item> items;
extern vector<Fireball> fireballs;
extern vector<Explosion> explosions;
extern vector<Coin> coins;
extern vector<BlockParticle> blockParticles;
extern vector<CoinIcon> coinIcons;
extern vector<UI> uis;
extern vector<ScoreNumber> scoreNumbers;

///Global classes
extern AudioManager audioManager;

///Global variables
extern bool isPaused;
extern int inGame;
extern float loadTimer;
extern int level;
extern int area;
extern int areaType;
extern int lives;
extern pause pauseCounter;
extern int score;
extern int coinCounter;
extern float timeLimit;
extern std::string requestedMusic;
extern std::string currentMusic;

///Resources
extern sf::Texture tilesheet;
extern sf::Texture blockParticle;
extern sf::Texture castle;
extern sf::Texture castleFlag;
extern sf::Texture castleDoor;
extern sf::Texture coin;
extern sf::Texture coinPickup;
extern sf::Texture explosion;
extern sf::Texture fireball;
extern sf::Texture flagpole;
extern sf::Texture flagPoleTop;
extern sf::Texture flagpoleFlag;
extern sf::Texture goomba;
extern sf::Texture item;
extern sf::Texture koopa;
extern sf::Texture livesIconTexture;
extern sf::Texture mario;

extern sf::Font pressStart2P;
