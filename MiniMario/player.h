#pragma once

#include "animation.h"
#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
        ~Player();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetSpritePosition() {return sprite.getPosition();}
        sf::Vector2f GetHalfSize()
        {
            sf::Vector2f tmpSize = body.getSize();
            tmpSize.x = 24.0f;
            return tmpSize / 2.0f;
        }
        void SetRow(int index, float deltaTime);
        void SetColumn (int indexBegin, int indexEnd, float deltaTime);
        void SetSize(sf::Vector2f size) {body.setSize(size);}
        void SetVelocity(float x, float y)
        {
            velocity.x = x;
            velocity.y = y;
        }
        void Move(sf::Vector2f move) {body.move(move);}
        void MoveSprite(sf::Vector2f move) {sprite.move(move);}
        void SetPosition(sf::Vector2f position) {body.setPosition(position);}
        void SetSpritePosition(sf::Vector2f position) {sprite.setPosition(position);}
        void Reset();
        void Hurt(int type);

        int isBig;
        int state;
        bool isCrouching;
        int isGrabbing;
        int grabDistance;
        float grabTimer;
        int isWarping;
        int warpDirection;
        float warpTimer;
        int currentWarp;
        int warpIndex;
        int streak;
        float graceTimer;
        int shellInvincibility;
        float deathTimer;
        float invincibilityTimer;

    private:
        ///Physics functions
        float DistanceToBlock(int direction);
        /**
        0 = Below
        1 = Above
        2 = Left
        3 = Right
        */

        ///Display
        sf::RectangleShape body;
        sf::RectangleShape sprite;
        Animation animation;
        unsigned int row;
        unsigned int columnBegin;
        unsigned int columnEnd;
        float switchTime;
        bool faceRight;
        ///Movement
        sf::Vector2f velocity;
        float speed;
        float jumpHeight;
        bool canJump;
        float fireballTimer;
        bool shiftReleased;
        int crouchDirection;

        ///ANIMATION LEGEND
        /**
        ? = Not used
        ??? = Not used and have no idea what the animation is used for

        ROWS:
        0 = Small Mario
        1 = Big Mario
        2 = Small Luigi?
        3 = Big Luigi?
        4 = Small fire?
        5 = Big fire
        6 = Small Invincible 1
        7 = Big Invincible 1
        8 = Small Invincible 2 (Overworld)
        9 = Big Invincible 2 (Overworld)
        10 = Small Invincible 3 (Overworld)
        11 = Big Invincible 3 (Overworld)
        12 = SmallInvincible 2 (Underground)
        13 = Big Invincible 2 (Underground)
        14 = Small Invincible 3 (Underground / Castle)
        15 = Big Invincible 3 (Underground / Castle)
        16 = Small Invincible 2 (Castle)?
        17 = Big Invincible 2 (Castle)?
        18 = Small Invincible 2 (Underwater)?
        19 = Big Invincible 2 (Underwater)?
        20 = Small Invincible 3 (Underwater)?
        21 = Big Invincible 3 (Underwater)?

        COLUMNS:
        Small:
        0 = Idle
        1 - 4 = Running
        5 = Turning
        6 = Jumping
        7 = Death
        8 - 9 = Grabbing
        10 - 11 = Swimming idle?
        12 - 15 = Swimming?

        Big:
        0 = Idle
        1 - 4 = Running
        5 = Turning
        6 = Jumping
        7 = Ducking
        8 - 9 = Grabbing
        10 - 11 = Swimming idle?
        12 - 15 = Swimming?
        16 = Enlarged Head (For the power up animation)
        17 - 21 = Walking underwater???
        */
};
