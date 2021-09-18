#include "header.h"
#include "player.h"

///Constructor
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
    animation(texture, imageCount, switchTime) ///Initialize an instance of the "Animation" class to go along with this object
{
    ///Construct body and sprite rectangles
    body.setSize(sf::Vector2f(24.0f, 30.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(64.0f, 256.0f);
    sprite.setSize(sf::Vector2f(32.0f, 64.0f));
    sprite.setOrigin(sprite.getSize() / 2.0f);
    sprite.setPosition(body.getPosition());
    sprite.setTexture(texture);
    ///Initialize all variables that need to be set
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->row = 0;
    this->columnBegin = 0;
    this->columnEnd = 1;
    this->switchTime = switchTime;
    this->faceRight = true;
    this->isBig = 0;
    this->fireballTimer = 0.0f;
    this->graceTimer = 0.0f;
    this->shellInvincibility = -1;
    this->deathTimer = -1.0f;
    this->streak = 1;
    this->isGrabbing = 0;
    this->grabDistance = 0.0f;
    this->grabTimer = 0.0f;
    this->isWarping = 0;
    this->warpDirection = -1;
    this->warpTimer = -1.0f;
    this->currentWarp = -1;
    this->warpIndex = -1;
    this->invincibilityTimer = -1.0f;
    this->crouchDirection = 0;
}

///Destructor (No idea what this is)
Player::~Player()
{
    //dtor
}

///Used to get information about the block above the player, if there is one
blockType GetBlock (sf::Vector2f position)
{
    ///Struct variable to store information
    blockType tmpBlockType;

    ///Run through each list
    for (int i = 0; i < breakableBlocks.size(); i++)
    {
        ///Check the positions of every block
        sf::Vector2f blockPos = breakableBlocks[i].GetPosition();
        if (position.x > blockPos.x - 16 && position.x < blockPos.x + 16)
        {
            if (position.y > blockPos.y - 16 && position.y < blockPos.y + 16)
            {
                ///If positions match, provide information through the struct variable
                tmpBlockType.index = 1;
                tmpBlockType.location = i;
                tmpBlockType.type = breakableBlocks[i].GetType();
                tmpBlockType.param = breakableBlocks[i].GetParam();
                ///Return information
                return tmpBlockType;
            }
        }
    }

    for (int i = 0; i < unbreakableBlocks.size(); i++)
    {
        sf::Vector2f blockPos = unbreakableBlocks[i].GetPosition();
        if (position.x > blockPos.x - 16 && position.x < blockPos.x + 16)
        {
            if (position.y > blockPos.y - 16 && position.y < blockPos.y + 16)
            {
                tmpBlockType.index = 2;
                tmpBlockType.location = i;
                tmpBlockType.type = unbreakableBlocks[i].GetType();
                return tmpBlockType;
            }
        }
    }

    for (int i = 0; i < questionBlocks.size(); i++)
    {
        sf::Vector2f blockPos = questionBlocks[i].GetPosition();
        if (position.x > blockPos.x - 16 && position.x < blockPos.x + 16)
        {
            if (position.y > blockPos.y - 16 && position.y < blockPos.y + 16)
            {
                tmpBlockType.index = 3;
                tmpBlockType.location = i;
                tmpBlockType.type = questionBlocks[i].GetType();
                tmpBlockType.param = questionBlocks[i].GetParam();
                return tmpBlockType;
            }
        }
    }

    for (int i = 0; i < pipes.size(); i++)
    {
        sf::Vector2f blockPos = pipes[i].GetPosition();
        if (position.x > blockPos.x - 16 && position.x < blockPos.x + 16)
        {
            if (position.y > blockPos.y - 16 && position.y < blockPos.y + 16)
            {
                tmpBlockType.index = 4;
                tmpBlockType.location = i;
                //tmpBlockType.type = pipes[i].GetType();
                return tmpBlockType;
            }
        }
    }

    ///If the position does not match anything, return -1 on everything
    tmpBlockType.index = -1;
    tmpBlockType.location = -1;
    tmpBlockType.type = -1;
    tmpBlockType.param = -1;
    return tmpBlockType;
}

///Physics engine
float Player::DistanceToBlock(int direction)
{
    float distance = 999999.0f;
    sf::Vector2f blockPos;
    int location;
    int index = 0;

    float bodyHeight;
    if (isBig < 1 || isCrouching)
    {
        bodyHeight = 16;
    }
    else
    {
        bodyHeight = 32;
    }

    ///Below
    if (direction == 0)
    {
        for (int i = 0; i < breakableBlocks.size(); i++)
        {
            blockPos = breakableBlocks[i].GetPosition();
            bool isBlock = false;

            ///If the current block being checked is below the player on the y axis
            if (blockPos.y - 16 >= body.getPosition().y + bodyHeight)
            {
                ///If the current block is both under the player on the y axis and the player lines up with it on the x axis
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                ///If the previous conditions are true, then find the distance of the block and set it aside
                if (isBlock)
                {
                    if (blockPos.y - 16 - (body.getPosition().y + bodyHeight) < distance)
                    {
                        distance = blockPos.y - 16 - (body.getPosition().y + bodyHeight);
                        location = i;
                        index = 1;
                    }
                }
            }
        }

        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            blockPos = unbreakableBlocks[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y - 16 >= body.getPosition().y + bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if (blockPos.y - 16 - (body.getPosition().y + bodyHeight) < distance)
                    {
                        distance = blockPos.y - 16 - (body.getPosition().y + bodyHeight);
                        location = i;
                        index = 2;
                    }
                }
            }
        }

        for (int i = 0; i < questionBlocks.size(); i++)
        {
            blockPos = questionBlocks[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y - 16 >= body.getPosition().y + bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if (blockPos.y - 16 - (body.getPosition().y + bodyHeight) < distance)
                    {
                        distance = blockPos.y - 16 - (body.getPosition().y + bodyHeight);
                        location = i;
                        index = 3;
                    }
                }
            }
        }

        for (int i = 0; i < pipes.size(); i++)
        {
            blockPos = pipes[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y - 16 >= body.getPosition().y + bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if (blockPos.y - 16 - (body.getPosition().y + bodyHeight) < distance)
                    {
                        distance = blockPos.y - 16 - (body.getPosition().y + bodyHeight);
                        location = i;
                        index = 4;
                    }
                }
            }
        }
    }
    ///Above
    else if (direction == 1)
    {
        for (int i = 0; i < breakableBlocks.size(); i++)
        {
            blockPos = breakableBlocks[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y + 16 <= body.getPosition().y - bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if ((body.getPosition().y - bodyHeight) - blockPos.y + 16 < distance)
                    {
                        distance = (body.getPosition().y - bodyHeight) - blockPos.y + 16;
                        location = i;
                        index = 1;
                    }
                }
            }
        }

        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            blockPos = unbreakableBlocks[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y + 16 <= body.getPosition().y - bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if ((body.getPosition().y - bodyHeight) - blockPos.y + 16 < distance)
                    {
                        distance = (body.getPosition().y - bodyHeight) - blockPos.y + 16;
                        location = i;
                        index = 2;
                    }
                }
            }
        }

        for (int i = 0; i < questionBlocks.size(); i++)
        {
            blockPos = questionBlocks[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y + 16 <= body.getPosition().y - bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if ((body.getPosition().y - bodyHeight) - blockPos.y + 16 < distance)
                    {
                        distance = (body.getPosition().y - bodyHeight) - blockPos.y + 16;
                        location = i;
                        index = 3;
                    }
                }
            }
        }

        for (int i = 0; i < pipes.size(); i++)
        {
            blockPos = pipes[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y + 16 <= body.getPosition().y - bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if ((body.getPosition().y - bodyHeight) - blockPos.y + 16 < distance)
                    {
                        distance = (body.getPosition().y - bodyHeight) - blockPos.y + 16;
                        location = i;
                        index = 4;
                    }
                }
            }
        }
    }
    ///Left
    else if (direction == 2)
    {
        for (int i = 0; i < breakableBlocks.size(); i++)
        {
            blockPos = breakableBlocks[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 1;
                }
            }
        }

        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            blockPos = unbreakableBlocks[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 2;
                }
            }
        }

        for (int i = 0; i < questionBlocks.size(); i++)
        {
            blockPos = questionBlocks[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 3;
                }
            }
        }

        for (int i = 0; i < pipes.size(); i++)
        {
            blockPos = pipes[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                    index = 4;
                }
            }
        }
    }
    ///Right
    else if (direction == 3)
    {
        for (int i = 0; i < breakableBlocks.size(); i++)
        {
            blockPos = breakableBlocks[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 1;
                }
            }
        }

        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            blockPos = unbreakableBlocks[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 2;
                }
            }
        }

        for (int i = 0; i < questionBlocks.size(); i++)
        {
            blockPos = questionBlocks[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 3;
                }
            }
        }

        for (int i = 0; i < pipes.size(); i++)
        {
            blockPos = pipes[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                    index = 4;
                }
            }
        }
    }

    if (distance == 999999.0f)
    {
        return 999999.0f;
    }
    else
    {
        if (direction == 0)
        {
            if (index == 1)
            {
                return breakableBlocks[location].GetPosition().y - 16 - (body.getPosition().y + bodyHeight);
            }
            else if (index == 2)
            {
                return unbreakableBlocks[location].GetPosition().y - 16 - (body.getPosition().y + bodyHeight);
            }
            else if (index == 3)
            {
                return questionBlocks[location].GetPosition().y - 16 - (body.getPosition().y + bodyHeight);
            }
            else if (index == 4)
            {
                return pipes[location].GetPosition().y - 16 - (body.getPosition().y + bodyHeight);
            }
        }
        else if (direction == 1)
        {
            if (index == 1)
            {
                return (body.getPosition().y - bodyHeight) - (breakableBlocks[location].GetPosition().y + 16);
            }
            else if (index == 2)
            {
                return (body.getPosition().y - bodyHeight) - (unbreakableBlocks[location].GetPosition().y + 16);
            }
            else if (index == 3)
            {
                return (body.getPosition().y - bodyHeight) - (questionBlocks[location].GetPosition().y + 16);
            }
            else if (index == 4)
            {
                return (body.getPosition().y - bodyHeight) - (pipes[location].GetPosition().y + 16);
            }
        }
        else if (direction == 2)
        {
            if (index == 1)
            {
                return (body.getPosition().x - 12) - (breakableBlocks[location].GetPosition().x + 16);
            }
            else if (index == 2)
            {
                return (body.getPosition().x - 12) - (unbreakableBlocks[location].GetPosition().x + 16);
            }
            else if (index == 3)
            {
                return (body.getPosition().x - 12) - (questionBlocks[location].GetPosition().x + 16);
            }
            else if (index == 4)
            {
                return (body.getPosition().x - 12) - (pipes[location].GetPosition().x + 16);
            }
        }
        else if (direction == 3)
        {
            if (index == 1)
            {
                return (breakableBlocks[location].GetPosition().x - 16) - (body.getPosition().x + 12);
            }
            else if (index == 2)
            {
                return (unbreakableBlocks[location].GetPosition().x - 16) - (body.getPosition().x + 12);
            }
            else if (index == 3)
            {
                return (questionBlocks[location].GetPosition().x - 16) - (body.getPosition().x + 12);
            }
            else if (index == 4)
            {
                return (pipes[location].GetPosition().x - 16) - (body.getPosition().x + 12);
            }
        }
    }
}

///Update function----------------------------------------------------------------------------------------------------
void Player::Update(float deltaTime)
{
    ///Set body size based on states
    if (isBig <= 0 || isCrouching)
    {
        body.setSize(sf::Vector2f(24.0f, 30.0f));
    }
    else if (isBig > 0 && !isCrouching)
    {
        body.setSize(sf::Vector2f(24.0f, 62.0f));
    }
    ///Set origin to always be in the center
    body.setOrigin(body.getSize() / 2.0f);

    ///If the player has not grabbed onto the flagpole
    if (isGrabbing == 0)
    {
        ///Reset ghost effect
        sprite.setFillColor(sf::Color(255, 255, 255, 255));

        ///If the player is not dead
        if (deathTimer == -1 || deathTimer > 0.6f)
        {
            if (isWarping == 0)
            {
                ///Decrease horizontal movement speed
                ///The speed will decrease faster if the player is on the ground and is not pressing "A" or "D"
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
                {
                    velocity.x *= 0.995f;
                }
                else
                {
                    velocity.x *= 0.9f;
                }

                ///Restrict maximum horizontal movement speed
                if (velocity.x > 490.5f)
                {
                    velocity.x = 490.5f;
                }
                if (velocity.x < -490.5f)
                {
                    velocity.x = -490.5f;
                }

                ///Set X velocity to 0 when small enough
                if (abs(velocity.x) < 0.1f)
                {
                    velocity.x = 0.0f;
                }

                ///Add to and limit gravity
                if (velocity.y < 981.0f)
                {
                    velocity.y += 3433.5f * deltaTime;//9.81f;
                }
                else
                {
                    velocity.y = 981.0f;
                }

                ///The player will be able to control their movement if they are not dead
                if (isBig > -1) ///If isBig is smaller than 0, it means the player has died
                {
                    ///The player will not be able to move while crouching
                    if (!isCrouching)
                    {
                        ///Horizontal movement
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        {
                            ///If the player is sprinting
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            {
                                velocity.x -= speed;
                            }
                            ///If the player is not sprinting
                            else
                            {
                                velocity.x -= speed / 2;
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            {
                                velocity.x += speed;
                            }
                            else
                            {
                                velocity.x += speed / 2;
                            }
                        }
                    }

                    ///Vertical movement
                    ///If the player is on the ground, then reset their streak, and allow them to jump again
                    if (DistanceToBlock(0) == 0.0f)
                    {
                        streak = 1;
                        ///To prevent the player from holding down the jump key
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        {
                            canJump = true;
                        }
                    }
                    else
                    {
                        canJump = false;
                    }

                    ///If the player presses W and canJump is true, jump
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        if (canJump)
                        {
                            audioManager.PlayAudio("jump");
                            velocity.y = -sqrt(/*2.0 * */981.0f * jumpHeight); //9.81f
                        }
                        canJump = false;
                    }

                    ///Do crouching
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && isBig > 0)// && DistanceToBlock(0) == 0.0f)
                    {
                        ///If the player was not originally crouching, then set their position after they crouch to be on the ground
                        if (!isCrouching)
                        {
                            body.setSize(sf::Vector2f(24.0f, 30.0f));
                            body.setOrigin(body.getSize() / 2.0f);
                            body.move(0.0f, 16.0f);
                        }
                        isCrouching = true;
                    }
                    else// if (isCrouching)
                    {
                        if (isBig > 0)
                        {
                            ///Check for blocks above
                            bool isBlockAbove = false;

                            if (isCrouching)
                            {
                                ///The direction to push the player
                                int direction = 1;
                                ///Variables that store the amount of blocks above the player on either side
                                int blocksToLeft = 0;
                                int blocksToRight = 0;
                                ///If the only block above the player is directly above them
                                bool bothSame = false;

                                ///Temporary check variable
                                sf::Vector2f tmpPos = body.getPosition();
                                tmpPos.y -= 32.0f;

                                ///If there is a block directly above the player
                                if (DistanceToBlock(1) < 1.0f)
                                {
                                    ///Check to left
                                    tmpPos.x = body.getPosition().x;
                                    while (GetBlock(tmpPos).index != -1)
                                    {
                                        tmpPos.x -= 32.0f;
                                        blocksToLeft++;
                                    }
                                    ///Check to right
                                    tmpPos.x = body.getPosition().x;
                                    while (GetBlock(tmpPos).index != -1)
                                    {
                                        tmpPos.x += 32.0f;
                                        blocksToRight++;
                                    }

                                    ///Only 1 block or less
                                    if (blocksToLeft < 2 && blocksToRight < 2)
                                    {
                                        bothSame = true;
                                    }
                                    ///Same on either side
                                    else if (blocksToLeft == blocksToRight)
                                    {
                                        bothSame = true;
                                    }
                                    ///Less blocks on left
                                    else if (blocksToLeft < blocksToRight)
                                    {
                                        direction = 0;
                                    }
                                    ///Less blocks on right
                                    else if (blocksToLeft > blocksToRight)
                                    {
                                        direction = 1;
                                    }

                                    ///If there is only the 1 block above the player, then we determine which direction to
                                    ///push the player by using the player's position in relation with the current block
                                    if (bothSame)
                                    {
                                        ///Get the player's current position
                                        tmpPos.x = body.getPosition().x + 12.0f;
                                        ///Get the position of the block above the player
                                        sf::Vector2f otherPos;
                                        if (GetBlock(tmpPos).index == 1)
                                        {
                                            otherPos = breakableBlocks[GetBlock(tmpPos).location].GetPosition();
                                        }
                                        else if (GetBlock(tmpPos).index == 2)
                                        {
                                            otherPos = unbreakableBlocks[GetBlock(tmpPos).location].GetPosition();
                                        }
                                        else if (GetBlock(tmpPos).index == 3)
                                        {
                                            otherPos = questionBlocks[GetBlock(tmpPos).location].GetPosition();
                                        }
                                        else if (GetBlock(tmpPos).index == 4)
                                        {
                                            otherPos = pipes[GetBlock(tmpPos).location].GetPosition();
                                        }

                                        ///If the player is on the left side of the block, deltaX will be positive
                                        ///If the player is on the right, deltaX will be negative
                                        float deltaX = otherPos.x - tmpPos.x;

                                        ///Left or pixel perfectly centered
                                        if (deltaX >= 0.0f)
                                        {
                                            direction = 0;
                                        }
                                        ///Right
                                        else if (deltaX < 0.0f)
                                        {
                                            direction = 1;
                                        }
                                    }

                                    ///Move to the left
                                    if (direction == 0)
                                    {
                                        body.move(-122.625f * deltaTime, 0.0f);
                                    }
                                    ///Move to the right
                                    else if (direction == 1)
                                    {
                                        body.move(122.625f * deltaTime, 0.0f);
                                    }
                                    isBlockAbove = true;
                                }
                            }

                            ///If the player is out of the blocks, then they can stop crouching
                            if (!isBlockAbove)
                            {
                                ///Reset player's position so that they don't move into the ground after uncrouching
                                if (isCrouching)
                                {
                                    body.move(0.0f, -16.0f);
                                }
                                isCrouching = false;
                            }
                            else
                            {
                                isCrouching = true;
                            }
                        }
                        ///If the player stops crouching because they took damage and are no longer big
                        else
                        {
                            if (isCrouching)
                            {
                                body.move(0.0f, -16.0f);
                            }
                            isCrouching = false;
                        }
                    }

                    ///FIREBALL!
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        ///The player can only create a new fireball if there are not already 2 fireballs in the game, and they are not holding down the left shift key
                        if (isBig == 2 && fireballs.size() < 2 && shiftReleased)
                        {
                            ///Create a new instance of the Fireball class
                            fireballs.push_back(Fireball(&fireball, sf::Vector2f(16.0f, 16.0f), GetPosition(), faceRight));
                            ///Timer to play animation
                            fireballTimer = 0.5f;
                            ///To prevent the player from holding down the shift key to spam fireballs
                            shiftReleased = false;
                            ///Play audio
                            audioManager.PlayAudio("fireball");
                        }
                    }
                    else
                    {
                        ///Reset
                        shiftReleased = true;
                    }

                    ///Decrease the animation timer
                    fireballTimer -= deltaTime;

                    ///Horizontal collision
                    if (velocity.x > 0.0f)
                    {
                        ///Make sure the player does not move into a wall
                        if (DistanceToBlock(3) < velocity.x * deltaTime)
                        {
                            velocity.x = 0.0f;
                            ///Stick as close to the wall as possible without entering it
                            body.move(DistanceToBlock(3), 0.0f);
                        }
                    }
                    else if (velocity.x < 0.0f)
                    {
                        if (DistanceToBlock(2) < abs(velocity.x) * deltaTime)
                        {
                            velocity.x = 0.0f;
                            body.move(-DistanceToBlock(2), 0.0f);
                        }
                    }

                    ///Vertical collision
                    ///Ground
                    ///Same as with wall, stick as close to the ground as possible without entering it
                    if (DistanceToBlock(0) < velocity.y * deltaTime)
                    {
                        velocity.y = 0.0f;
                        body.move(0.0f, DistanceToBlock(0));
                    }

                    ///Ceiling
                    ///Same as Ground and Wall
                    if (DistanceToBlock(1) != 999999.0f)
                    {
                        if (-DistanceToBlock(1) > velocity.y * deltaTime)
                        {
                            ///Stop player from moving upwards
                            velocity.y = 0.0f;
                            body.move(0.0f, -DistanceToBlock(1));

                            ///Check and trigger block conditions if the player hits a block that is above them
                            sf::Vector2f tmpPos = body.getPosition();
                            if (isBig == 0 || isCrouching)
                            {
                                tmpPos.y -= 32.0f;
                            }
                            else
                            {
                                tmpPos.y -= 48.0f;
                            }

                            ///Check directly above the player's origin, above the left side of the player, and above the right side of the player
                            for (int i = 0; i < 3; i++)
                            {
                                if (i == 0)
                                {
                                    tmpPos.x = body.getPosition().x;
                                }
                                else if (i == 1)
                                {
                                    tmpPos.x = body.getPosition().x - 12.0f;
                                }
                                else if (i == 2)
                                {
                                    tmpPos.x = body.getPosition().x + 12.0f;
                                }
                                ///Breakable blocks
                                if (GetBlock(tmpPos).index == 1)
                                {
                                    breakableBlocks[GetBlock(tmpPos).location].OnCollision(isBig);
                                    break;
                                }
                                ///Question blocks
                                else if (GetBlock(tmpPos).index == 3)
                                {
                                    questionBlocks[GetBlock(tmpPos).location].OnCollision(isBig);
                                    break;
                                }
                            }
                        }
                    }

                    ///Set X velocity to 0 after colliding with wall
                    if (DistanceToBlock(2) <= 1.0f && velocity.x < 0.0f)
                    {
                        velocity.x = 0.0f;
                    }

                    if (DistanceToBlock(3) <= 1.0f && velocity.x > 0.0f)
                    {
                        velocity.x = 0.0f;
                    }

                    ///Backup collision engines
                    for (int i = 0; i < breakableBlocks.size(); i++)
                    {
                        ///Get information about the positions and size of the player and the block we are colliding with
                        sf::Vector2f otherPos = breakableBlocks[i].GetPosition();
                        sf::Vector2f otherHalfSize = breakableBlocks[i].GetHalfSize();
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();

                        ///The position of the block's origin point subtract the position of the player's origin point
                        ///Basically the distance between the origins, but when the player is on the left on the block,
                        ///deltaX will be positive, when the player is above the block, deltaY will be positive, and vice versa
                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        ///The distance between the SIDE of the player and the SIDE of the block, including their half sizes in the calculation
                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        ///If the intersects are both negative, it means the player has entered the block
                        if (intersectX < 0.0f && intersectY < 0.0f)
                        {
                            ///If the player entered the block from the sides
                            if (intersectX > intersectY)
                            {
                                ///Left
                                if (deltaX > 0.0f)
                                {
                                    ///Push the player out of the block and reset their velocity
                                    body.move(intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                                ///Right
                                else if (deltaX < 0.0f)
                                {
                                    body.move(-intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                            }
                            ///If the player entered the block from the top or bottom
                            else
                            {
                                ///Top
                                if (deltaY > 0.0f)
                                {
                                    body.move(0.0f, intersectY);
                                    velocity.y = 0.0f;
                                }
                                ///Bottom
                                else if (deltaY < 0.0f)
                                {
                                    body.move(0.0f, -intersectY);
                                    velocity.y = 0.0f;
                                }
                            }
                        }
                    }

                    ///Same as before
                    for (int i = 0; i < unbreakableBlocks.size(); i++)
                    {
                        sf::Vector2f otherPos = unbreakableBlocks[i].GetPosition();
                        sf::Vector2f otherHalfSize = unbreakableBlocks[i].GetHalfSize();
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();

                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        if (intersectX < 0.0f && intersectY < 0.0f)
                        {
                            if (intersectX > intersectY)
                            {
                                ///Left
                                if (deltaX > 0.0f)
                                {
                                    body.move(intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                                ///Right
                                else if (deltaX < 0.0f)
                                {
                                    body.move(-intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                            }
                            else
                            {
                                ///Top
                                if (deltaY > 0.0f)
                                {
                                    body.move(0.0f, intersectY);
                                    velocity.y = 0.0f;
                                }
                                ///Bottom
                                else if (deltaY < 0.0f)
                                {
                                    body.move(0.0f, -intersectY);
                                    velocity.y = 0.0f;
                                }
                            }
                        }
                    }

                    for (int i = 0; i < questionBlocks.size(); i++)
                    {
                        sf::Vector2f otherPos = questionBlocks[i].GetPosition();
                        sf::Vector2f otherHalfSize = questionBlocks[i].GetHalfSize();
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();

                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        if (intersectX < 0.0f && intersectY < 0.0f)
                        {
                            if (intersectX > intersectY)
                            {
                                ///Left
                                if (deltaX > 0.0f)
                                {
                                    body.move(intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                                ///Right
                                else if (deltaX < 0.0f)
                                {
                                    body.move(-intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                            }
                            else
                            {
                                ///Top
                                if (deltaY > 0.0f)
                                {
                                    body.move(0.0f, intersectY);
                                    velocity.y = 0.0f;
                                }
                                ///Bottom
                                else if (deltaY < 0.0f)
                                {
                                    body.move(0.0f, -intersectY);
                                    velocity.y = 0.0f;
                                }
                            }
                        }
                    }

                    for (int i = 0; i < pipes.size(); i++)
                    {
                        sf::Vector2f otherPos = pipes[i].GetPosition();
                        sf::Vector2f otherHalfSize = pipes[i].GetHalfSize();
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();

                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        if (intersectX < 0.0f && intersectY < 0.0f)
                        {
                            if (intersectX > intersectY)
                            {
                                ///Left
                                if (deltaX > 0.0f)
                                {
                                    body.move(intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                                ///Right
                                else if (deltaX < 0.0f)
                                {
                                    body.move(-intersectX, 0.0f);
                                    velocity.x = 0.0f;
                                }
                            }
                            else
                            {
                                ///Top
                                if (deltaY > 0.0f)
                                {
                                    body.move(0.0f, intersectY);
                                    velocity.y = 0.0f;
                                }
                                ///Bottom
                                else if (deltaY < 0.0f)
                                {
                                    body.move(0.0f, -intersectY);
                                    velocity.y = 0.0f;
                                }
                            }
                        }
                    }

                    ///Check collision with goombas
                    ///Now we no longer push the player out of the goomba, we instead do actions to the player and the goomba based on how they collide
                    for (int i = 0; i < goombas.size(); i++)
                    {
                        if (goombas[i].squishTimer == 0 && goombas[i].isFlipping == false && isBig > -1)
                        {
                            sf::Vector2f thisPos = GetPosition();
                            sf::Vector2f otherPos = goombas[i].GetPosition();
                            sf::Vector2f thisHalfSize = GetHalfSize();
                            sf::Vector2f otherHalfSize = goombas[i].GetHalfSize();

                            float deltaX = otherPos.x - thisPos.x;
                            float deltaY = otherPos.y - thisPos.y;

                            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                            if (intersectX < 0.0f && intersectY < 0.0f)
                            {
                                ///If the player has the effects of an invincibility star active, kill the goomba instantly
                                if (invincibilityTimer > 0.0f)
                                {
                                    goombas[i].Flip(streak);
                                }
                                else
                                {
                                    ///The goomba is above the player
                                    if (deltaY <= thisHalfSize.y - otherHalfSize.y + 1.0f)
                                    {
                                        Hurt(0);
                                    }
                                    ///The player is above the goomba
                                    else if (deltaY > thisHalfSize.y - otherHalfSize.y + 1.0f)
                                    {
                                        ///Stomp on the goomba
                                        goombas[i].Squish(streak);
                                        ///Make the player bounce back up
                                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                                        {
                                            velocity.y = -sqrt(981.0f * jumpHeight);
                                        }
                                        else
                                        {
                                            velocity.y = -sqrt(981.0f * jumpHeight / 4);
                                        }
                                        ///Increase their stomp streak so that the next stomp rewards more score
                                        streak++;
                                    }
                                }
                            }
                        }
                    }

                    ///Check collision with koopas
                    if (shellInvincibility == -1)
                    {
                        for (int i = 0; i < koopas.size(); i++)
                        {
                            if (!koopas[i].isFlipping && isBig > -1)
                            {
                                sf::Vector2f thisPos = GetPosition();
                                sf::Vector2f otherPos = koopas[i].GetPosition();
                                sf::Vector2f thisHalfSize = GetHalfSize();
                                sf::Vector2f otherHalfSize = koopas[i].GetHalfSize();

                                float deltaX = otherPos.x - thisPos.x;
                                float deltaY = otherPos.y - thisPos.y;

                                float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                                float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                                if (intersectX < 0.0f && intersectY < 0.0f)
                                {
                                    if (invincibilityTimer > 0.0f)
                                    {
                                        koopas[i].Flip(streak);
                                    }
                                    else
                                    {
                                        ///The koopa is on top
                                        if (deltaY <= thisHalfSize.y - otherHalfSize.y + 1.0f)
                                        {
                                            ///if the koopa is out of its shell
                                            if (koopas[i].state == 0)
                                            {
                                                Hurt(0);
                                            }
                                            ///If the koopa is in a stationary shell
                                            else if (koopas[i].state == 1)
                                            {
                                                koopas[i].Squish(0);
                                                if (deltaX < 0)
                                                {
                                                    koopas[i].direction = 0;
                                                }
                                                else
                                                {
                                                    koopas[i].direction = 1;
                                                }
                                                shellInvincibility = i;
                                            }
                                            ///If the koopa is in a rolling shell
                                            else if (koopas[i].state == 2)
                                            {
                                                Hurt(0);
                                            }
                                        }
                                        ///The koopa is on the bottom
                                        else if (deltaY > thisHalfSize.y - otherHalfSize.y + 1.0f)
                                        {
                                            ///If the player is jumping onto a koopa out of its shell
                                            if (koopas[i].state == 0)
                                            {
                                                koopas[i].Squish(streak);
                                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                                                {
                                                    velocity.y = -sqrt(981.0f * jumpHeight);
                                                }
                                                else
                                                {
                                                    velocity.y = -sqrt(981.0f * jumpHeight / 4);
                                                }
                                                ///Make sure the player does not immediately get damage by the same koopa's shell
                                                shellInvincibility = i;
                                            }
                                            ///Kicking a stationary shell
                                            else if (koopas[i].state == 1)
                                            {
                                                koopas[i].Squish(0);
                                                if (deltaX < 0)
                                                {
                                                    koopas[i].direction = 0;
                                                }
                                                else
                                                {
                                                    koopas[i].direction = 1;
                                                }
                                                shellInvincibility = i;
                                            }
                                            ///Stopping a rolling shell
                                            else if (koopas[i].state == 2)
                                            {
                                                koopas[i].Squish(0);
                                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                                                {
                                                    velocity.y = -sqrt(981.0f * jumpHeight);
                                                }
                                                else
                                                {
                                                    velocity.y = -sqrt(981.0f * jumpHeight / 4);
                                                }
                                                shellInvincibility = i;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    ///If the player has their shell invincibility active
                    else
                    {
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f otherPos = koopas[shellInvincibility].GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();
                        sf::Vector2f otherHalfSize = koopas[shellInvincibility].GetHalfSize();

                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        ///If the player is no longer in contact with the shell, reset their shell invincibility
                        if (intersectX > 0.0f || intersectY > 0.0f)
                        {
                            shellInvincibility = -1;
                        }
                    }

                    ///Check collision with coinPickups
                    for (int i = 0; i < coinPickups.size(); i++)
                    {
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f otherPos = coinPickups[i].GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();
                        sf::Vector2f otherHalfSize = coinPickups[i].GetHalfSize();

                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        if (intersectX < 0.0f && intersectY < 0.0f)
                        {
                            ///Add to the total coin count
                            coinCounter++;
                            ///Add to score and create a score number
                            score += 200;
                            scoreNumbers.push_back(ScoreNumber(&pressStart2P, coinPickups[i].GetPosition(), 200));
                            ///Audio
                            audioManager.PlayAudio("coin");
                            ///Delete the coin
                            coinPickups.erase(coinPickups.begin() + i);
                        }
                    }

                    ///Check collision with items
                    for (int i = 0; i < items.size(); i++)
                    {
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f otherPos = items[i].GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();
                        sf::Vector2f otherHalfSize = items[i].GetHalfSize();

                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        if (intersectX < 0.0f && intersectY < 0.0f)
                        {
                            ///If the player is not dead
                            if (isBig > -1)
                            {
                                ///If the player is currently small
                                if (isBig == 0)
                                {
                                    ///If the item is a mushroom
                                    if (items[i].type == 0)
                                    {
                                        ///Start the pause animation
                                        pauseCounter.before = 0;
                                        pauseCounter.after = 1;
                                        pauseCounter.switchTimer = 1.0f;
                                        ///Set the player's state
                                        isBig = 1;
                                        ///Create score
                                        score += 1000;
                                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, items[i].GetPosition(), 1000));
                                        audioManager.PlayAudio("powerup");
                                    }
                                    ///Fire flower
                                    else if (items[i].type == 1)
                                    {
                                        pauseCounter.before = 0;
                                        pauseCounter.after = 2;
                                        pauseCounter.switchTimer = 1.0f;
                                        isBig = 2;
                                        score += 1000;
                                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, items[i].GetPosition(), 1000));
                                        audioManager.PlayAudio("powerup");
                                    }
                                    ///Star
                                    else if (items[i].type == 2)
                                    {
                                        ///Give the player invincibility
                                        invincibilityTimer = 12.0f;
                                        score += 1000;
                                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, items[i].GetPosition(), 1000));
                                        audioManager.PlayAudio("powerup");
                                        ///Update music
                                        if (timeLimit > 100.0f)
                                        {
                                            requestedMusic = "invincible";
                                        }
                                        else if (timeLimit > 0.0f)
                                        {
                                            requestedMusic = "invincibleHurryUp";
                                        }
                                    }
                                }
                                ///If the player is currently big
                                else if (isBig == 1)
                                {
                                    if (items[i].type == 1)
                                    {
                                        pauseCounter.before = 1;
                                        pauseCounter.after = 2;
                                        pauseCounter.switchTimer = 1.0f;
                                        isBig = 2;
                                        score += 1000;
                                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, items[i].GetPosition(), 1000));
                                        audioManager.PlayAudio("powerup");
                                    }
                                    else if (items[i].type == 2)
                                    {
                                        invincibilityTimer = 12.0f;
                                        score += 1000;
                                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, items[i].GetPosition(), 1000));
                                        audioManager.PlayAudio("powerup");
                                        if (timeLimit > 100.0f)
                                        {
                                            requestedMusic = "invincible";
                                        }
                                        else if (timeLimit > 0.0f)
                                        {
                                            requestedMusic = "invincibleHurryUp";
                                        }
                                    }
                                }
                                ///If the player already has a fire flower
                                else if (isBig == 2)
                                {
                                    ///Just add score
                                    if (items[i].type == 0 || items[i].type == 1)
                                    {
                                        score += 1000;
                                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, items[i].GetPosition(), 1000));
                                    }
                                    else if (items[i].type == 2)
                                    {
                                        invincibilityTimer = 12.0f;
                                        score += 1000;
                                        scoreNumbers.push_back(ScoreNumber(&pressStart2P, items[i].GetPosition(), 1000));
                                        audioManager.PlayAudio("powerup");
                                        if (timeLimit > 100.0f)
                                        {
                                            requestedMusic = "invincible";
                                        }
                                        else if (timeLimit > 0.0f)
                                        {
                                            requestedMusic = "invincibleHurryUp";
                                        }
                                    }
                                }

                                items.erase(items.begin() + i);
                                shiftReleased = false;
                            }
                        }
                    }

                    ///Check collision with flagpole
                    for (int i = 0; i < flagpoles.size(); i++)
                    {
                        if (!flagpoles[i].grabbed && isBig > -1)
                        {
                            sf::Vector2f thisPos = GetPosition();
                            sf::Vector2f otherPos = sf::Vector2f(flagpoles[i].GetPosition().x, flagpoles[i].GetPosition().y - flagpoles[i].GetHalfSize().y);
                            sf::Vector2f thisHalfSize = GetHalfSize();
                            sf::Vector2f otherHalfSize = flagpoles[i].GetHalfSize();

                            float deltaX = otherPos.x - thisPos.x;
                            float deltaY = otherPos.y - thisPos.y;

                            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                            if (intersectX < 0.0f && intersectY < 0.0f)
                            {
                                ///If the player is not already grabbing
                                if (isGrabbing == 0)
                                {
                                    ///Reset the player's fireball animation
                                    fireballTimer = 0.0f;
                                    ///Play sound effect
                                    audioManager.PlayAudio("flagpole");
                                    ///Stop all music
                                    requestedMusic = "";
                                    ///Update the flagpole
                                    flagpoles[i].grabbed = true;
                                    flagpoles[i].SetScoreText();
                                    ///Update player's state
                                    grabDistance = abs(otherPos.y + otherHalfSize.y - thisPos.y);
                                    isGrabbing = 1;
                                }
                            }
                        }
                    }

                    ///Check collision with warps
                    for (int i = 0; i < warps.size(); i++)
                    {
                        sf::Vector2f thisPos = GetPosition();
                        sf::Vector2f otherPos = warps[i].GetPosition();
                        sf::Vector2f thisHalfSize = GetHalfSize();
                        sf::Vector2f otherHalfSize = warps[i].GetHalfSize();

                        float deltaX = otherPos.x - thisPos.x;
                        float deltaY = otherPos.y - thisPos.y;

                        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
                        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

                        if (intersectX < 0.0f && intersectY < 0.0f && canJump)
                        {
                            ///Top
                            if (warps[i].direction == 1)
                            {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                                {
                                    ///Play sound effect
                                    audioManager.PlayAudio("pipe");
                                    ///Set the player's state
                                    isWarping = 1;
                                    warpDirection = 0;
                                    warpTimer = 1.0f;
                                    currentWarp = i;
                                    warpIndex = warps[i].GetWarp();
                                }
                            }
                            ///Bottom
                            if (warps[i].direction == 2)
                            {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                                {
                                    audioManager.PlayAudio("pipe");
                                    isWarping = 1;
                                    warpDirection = 1;
                                    warpTimer = 1.0f;
                                    currentWarp = i;
                                    warpIndex = warps[i].GetWarp();
                                }
                            }
                            ///Left
                            if (warps[i].direction == 3)
                            {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                                {
                                    audioManager.PlayAudio("pipe");
                                    isWarping = 1;
                                    warpDirection = 2;
                                    warpTimer = 1.0f;
                                    currentWarp = i;
                                    warpIndex = warps[i].GetWarp();
                                }
                            }
                            ///Right
                            if (warps[i].direction == 4)
                            {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                                {
                                    audioManager.PlayAudio("pipe");
                                    isWarping = 1;
                                    warpDirection = 3;
                                    warpTimer = 1.0f;
                                    currentWarp = i;
                                    warpIndex = warps[i].GetWarp();
                                }
                            }
                        }
                    }
                }

                ///Check if player has fallen below the level
                if (body.getPosition().y > 736.0f) //640.0f)
                {
                    if (isBig > -1)
                    {
                        ///Instantly kill the player
                        Hurt(1);
                    }
                }
            }
            ///Warp handler
            else if (isWarping == 1)
            {
                ///At the beginning of warping
                if (warpTimer == 1.0f)
                {
                    ///Set the player's position to match the animation
                    if (isBig == 0)
                    {
                        body.setPosition(warps[currentWarp].GetPosition());
                    }
                    else if (isBig == 1 || isBig == 2)
                    {
                        if (warps[currentWarp].direction == 1)
                        {
                            body.setPosition(sf::Vector2f(warps[currentWarp].GetPosition().x, warps[currentWarp].GetPosition().y + 16.0f));
                        }
                        else if (warps[currentWarp].direction == 2 || warps[currentWarp].direction == 3 || warps[currentWarp].direction == 4)
                        {
                            body.setPosition(sf::Vector2f(warps[currentWarp].GetPosition().x, warps[currentWarp].GetPosition().y - 16.0f));
                        }

                        isCrouching = false;
                    }
                    warpTimer -= deltaTime;
                }
                ///During the animation
                else if (warpTimer > 0.0f)
                {
                    ///Make the player move in the direction matching to the current warp
                    if (warps[currentWarp].direction == 1)
                    {
                        velocity.x = 0.0f;
                        velocity.y = -64.0f;
                    }
                    else if (warps[currentWarp].direction == 2)
                    {
                        velocity.x = 0.0f;
                        velocity.y = 64.0f;
                    }
                    else if (warps[currentWarp].direction == 3)
                    {
                        velocity.x = -32.0f;
                        velocity.y = 0.0f;
                    }
                    else if (warps[currentWarp].direction == 4)
                    {
                        velocity.x = 32.0f;
                        velocity.y = 0.0f;
                    }
                    warpTimer -= deltaTime;
                }
                ///if the animation has finished
                else if (warpTimer <= 0.0f)
                {
                    ///Go to the correct area and update music to match that area
                    if (level == 11)
                    {
                        if (warps[warpIndex].index == 0)
                        {
                            area = 1;
                            if (invincibilityTimer > 0.0f)
                            {
                                if (timeLimit > 100.0f)
                                {
                                    requestedMusic = "invincible";
                                }
                                else if (timeLimit > 0.0f)
                                {
                                    requestedMusic = "invincibleHurryUp";
                                }
                            }
                            else if (timeLimit > 100.0f)
                            {
                                requestedMusic = "underground";
                            }
                            else if (timeLimit > 0.0f)
                            {
                                requestedMusic = "undergroundHurryUp";
                            }
                        }
                        else if (warps[warpIndex].index == 1)
                        {
                            area = 0;
                            if (invincibilityTimer > 0.0f)
                            {
                                if (timeLimit > 100.0f)
                                {
                                    requestedMusic = "invincible";
                                }
                                else if (timeLimit > 0.0f)
                                {
                                    requestedMusic = "invincibleHurryUp";
                                }
                            }
                            else if (timeLimit > 100.0f)
                            {
                                requestedMusic = "overworld";
                            }
                            else if (timeLimit > 0.0f)
                            {
                                requestedMusic = "overworldHurryUp";
                            }
                        }
                    }

                    ///If the target warp is just a drop
                    if (warps[warpIndex].direction == 0)
                    {
                        warpTimer = -1.0f;
                        body.setPosition(warps[warpIndex].GetPosition());
                        isWarping = 0;
                    }
                    else
                    {
                        ///The target warp is on top
                        if (warps[warpIndex].direction == 1 || warps[warpIndex].direction == 5)
                        {
                            warpTimer = 1.0f;
                            if (isBig < 1)
                            {
                                body.setPosition(sf::Vector2f(warps[warpIndex].GetPosition().x, warps[warpIndex].GetPosition().y - 64.0f));
                            }
                            else if (isBig > 0)
                            {
                                body.setPosition(sf::Vector2f(warps[warpIndex].GetPosition().x, warps[warpIndex].GetPosition().y - 64.0f + (body.getSize().y / 2.0f) - 16.0f));
                            }
                        }
                        ///Bottom
                        else if (warps[warpIndex].direction == 2 || warps[warpIndex].direction == 6)
                        {
                            warpTimer = 1.0f;
                            if (isBig < 1)
                            {
                                body.setPosition(sf::Vector2f(warps[warpIndex].GetPosition().x, warps[warpIndex].GetPosition().y + 64.0f));
                            }
                            else if (isBig > 0)
                            {
                                body.setPosition(sf::Vector2f(warps[warpIndex].GetPosition().x, warps[warpIndex].GetPosition().y + 64.0f - (body.getSize().y / 2.0f) + 16.0f));
                            }
                        }
                        ///Left
                        else if (warps[warpIndex].direction == 3 || warps[warpIndex].direction == 7)
                        {
                            warpTimer = 1.0f;
                            body.setPosition(sf::Vector2f(warps[warpIndex].GetPosition().x - 32.0f + (body.getSize().x / 2.0f), warps[warpIndex].GetPosition().y));
                        }
                        ///Right
                        else if (warps[warpIndex].direction == 4 || warps[warpIndex].direction == 8)
                        {
                            warpTimer = 1.0f;
                            body.setPosition(sf::Vector2f(warps[warpIndex].GetPosition().x + 32.0f - (body.getSize().x / 2.0f), warps[warpIndex].GetPosition().y));
                        }
                        ///If the target warp needs an animation as well, start that animation
                        audioManager.PlayAudio("pipe");
                        isWarping = 2;
                    }
                }
            }
            ///If the target warp needs to perform an animation
            else if (isWarping == 2)
            {
                if (warpTimer > 0.0f)
                {
                    ///Set the player's movement based on direction
                    if (warps[warpIndex].direction == 1 || warps[warpIndex].direction == 5)
                    {
                        velocity.x = 0.0f;
                        velocity.y = 64.0f;
                    }
                    else if (warps[warpIndex].direction == 2 || warps[warpIndex].direction == 6)
                    {
                        velocity.x = 0.0f;
                        velocity.y = -64.0f;
                    }
                    else if (warps[warpIndex].direction == 3 || warps[warpIndex].direction == 7)
                    {
                        velocity.x = 32.0f;
                        velocity.y = 0.0f;
                    }
                    else if (warps[warpIndex].direction == 4 || warps[warpIndex].direction == 8)
                    {
                        velocity.x = -32.0f;
                        velocity.y = 0.0f;
                    }
                    warpTimer -= deltaTime;
                }
                ///After the animation finishes, return everything to normal
                else if (warpTimer <= 0.0f)
                {
                    //body.move(0.0f, -16.0f);
                    warpTimer = -1.0f;
                    isWarping = 0;
                    warpDirection = -1;
                    currentWarp = -1;
                    warpIndex = -1;
                }
            }

            ///Decrease grace and invincibility timers
            if (graceTimer > 0.0f)
            {
                ///Make the player flash during grace
                if ((int)((graceTimer * 10) + 0.5) % 2 == 1)
                {
                    sprite.setFillColor(sf::Color(255, 255, 255, 0));
                }
                else
                {
                    sprite.setFillColor(sf::Color(255, 255, 255, 255));
                }
                graceTimer -= deltaTime;
            }

            ///If the player is currently invincible
            if (invincibilityTimer > 0.0f)
            {
                invincibilityTimer -= deltaTime;
            }
            ///If the player's invincibility has finished
            else if (invincibilityTimer != -1.0f)
            {
                ///Reset music
                if (level == 11)
                {
                    if (area == 0)
                    {
                        if (timeLimit > 100.0f)
                        {
                            requestedMusic = "overworld";
                        }
                        else if (timeLimit > 0.0f)
                        {
                            requestedMusic = "overworldHurryUp";
                        }
                    }
                    else if (area == 1)
                    {
                        if (timeLimit > 100.0f)
                        {
                            requestedMusic = "underground";
                        }
                        else if (timeLimit > 0.0f)
                        {
                            requestedMusic = "undergroundHurryUp";
                        }
                    }
                }
                ///For unimplemented levels
                else
                {

                }
                ///Reset invincibility timer
                invincibilityTimer = -1.0f;
            }

            ///Move
            body.move(velocity * deltaTime);
        }

        ///Check if coins make up 100, if they do, give the player a life
        if (coinCounter >= 100)
        {
            coinCounter -= 100;
            lives++;
            audioManager.PlayAudio("oneUp");
        }

        ///If the player has died, start the death animation
        if (isBig == -1)
        {
            velocity.x = 0.0f;
            deathTimer += deltaTime;
            if (deathTimer >= 3)
            {
                isBig = -2;
            }
        }

        ///Check if the death animation has finished, if it has, reset everything
        if (isBig == -2)
        {
            lives--;
            if (lives > 0)
            {
                loadTimer = 3.0f;
                inGame = 1;
            }
            else
            {
                loadTimer = 5.0f;
                inGame = 3;
            }
            deathTimer = -1.0f;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            isBig = 0;
            faceRight = true;
            body.setPosition(64.0f, 256.0f);
        }
    }
    ///If the player has grabbed onto the flagpole
    else if (isGrabbing == 1)
    {
        ///Do animation timer
        grabTimer += deltaTime;

        ///Move the player so that they reach the bottom of the flagpole in exactly 1 second
        if (body.getPosition().y < flagpoles[0].GetPosition().y - body.getSize().y / 2.0f)
        {
            body.move(0.0f, grabDistance * deltaTime);
            body.setPosition(sf::Vector2f(flagpoles[0].GetPosition().x - (body.getSize().x / 2.0f), body.getPosition().y));
            faceRight = true;
        }
        else
        {
            body.setPosition(sf::Vector2f(flagpoles[0].GetPosition().x + (body.getSize().x / 2.0f), flagpoles[0].GetPosition().y - body.getSize().y / 2.0f));
            faceRight = false;
        }

        ///If the grab animation has finished
        if (grabTimer >= 1.0f)
        {
            ///Make the player jump up
            velocity.y = -sqrt(981.0f * jumpHeight);
            ///Reset grabDistance
            grabDistance = 0.0f;
            ///Change to next animation
            isGrabbing = 2;
        }
    }
    ///If the player has hopped off the flagpole
    else if (isGrabbing == 2)
    {
        ///Walk towards the castle
        velocity.x = 122.625f;

        ///Do gravity after the player hops off the flagpole
        if (velocity.y < 981.0f)
        {
            velocity.y += 3433.5f * deltaTime;
        }
        else
        {
            velocity.y = 981.0f;
        }

        ///Ground collision
        if (DistanceToBlock(0) < velocity.y * deltaTime)
        {
            velocity.y = 0.0f;
            body.move(0.0f, DistanceToBlock(0));
        }

        ///Just in case
        for (int i = 0; i < unbreakableBlocks.size(); i++)
        {
            sf::Vector2f otherPos = unbreakableBlocks[i].GetPosition();
            sf::Vector2f otherHalfSize = unbreakableBlocks[i].GetHalfSize();
            sf::Vector2f thisPos = GetPosition();
            sf::Vector2f thisHalfSize = GetHalfSize();

            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;

            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                if (intersectX > intersectY)
                {
                    ///Left
                    if (deltaX > 0.0f)
                    {
                        body.move(intersectX, 0.0f);
                        velocity.x = 0.0f;
                    }
                    ///Right
                    else if (deltaX < 0.0f)
                    {
                        body.move(-intersectX, 0.0f);
                        velocity.x = 0.0f;
                    }
                }
                else
                {
                    ///Top
                    if (deltaY > 0.0f)
                    {
                        body.move(0.0f, intersectY);
                        velocity.y = 0.0f;
                    }
                    ///Bottom
                    else if (deltaY < 0.0f)
                    {
                        body.move(0.0f, -intersectY);
                        velocity.y = 0.0f;
                    }
                }
            }
        }

        ///Check collision with the castle door
        for (int i = 0; i < castles.size(); i++)
        {
            sf::Vector2f otherPos = castles[i].GetPosition();
            sf::Vector2f otherHalfSize = castles[i].GetHalfSize();
            sf::Vector2f thisPos = GetPosition();
            sf::Vector2f thisHalfSize = GetHalfSize();

            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;

            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                ///After the player enters the castle, finish the level
                castles[i].levelFinished = true;
                castles[i].finishTimer = 4.0f;
                ///SEt the player to be invisible
                sprite.setFillColor(sf::Color(255, 255, 255, 0));
            }
        }

        ///Move the player
        body.move(velocity * deltaTime);
    }

    ///Update animations
    ///Death
    if (isBig < 0)
    {
        row = 0;
        columnBegin = 7;
        columnEnd = 7;
    }
    ///Small
    else if (isBig == 0)
    {
        ///Manage invincibility
        ///Switch between the different rows for invincibility
        if (invincibilityTimer == -1.0f)
        {
            row = 0;
        }
        else if (invincibilityTimer != -1.0f)
        {
            if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 0)
            {
                row = 0;
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 1)
            {
                row = 6;
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 2)
            {
                ///Each different area type has a different set of colours that needs to be switched between
                ///See the player's sprite sheet ("sprites/mario.png") to look at each different colour scheme
                if (level == 11)
                {
                    if (area == 0)
                    {
                        row = 8;
                    }
                    else if (area == 1)
                    {
                        row = 12;
                    }
                }
                else
                {
                    row = 8;
                }
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 3)
            {
                if (level == 11)
                {
                    if (area == 0)
                    {
                        row = 10;
                    }
                    else if (area == 1)
                    {
                        row = 14;
                    }
                }
                else
                {
                    row = 10;
                }
            }
        }

        ///Grabbing onto flagpole
        if (isGrabbing == 1)
        {
            columnBegin = 8;
            columnEnd = 9;
        }
        ///Using a warp pipe
        else if (isWarping == 1)
        {
            if (warps[currentWarp].direction == 1 || warps[currentWarp].direction == 2)
            {
                columnBegin = 0;
                columnEnd = 0;
            }
            else if (warps[currentWarp].direction == 3 || warps[currentWarp].direction == 4)
            {
                columnBegin = 1;
                columnEnd = 1;
            }
        }
        else if (isWarping == 2)
        {
            if (warps[warpIndex].direction == 1 || warps[warpIndex].direction == 2 || warps[warpIndex].direction == 5 || warps[warpIndex].direction == 6)
            {
                columnBegin = 0;
                columnEnd = 0;
            }
            else if (warps[warpIndex].direction == 3 || warps[warpIndex].direction == 4 || warps[warpIndex].direction == 7 || warps[warpIndex].direction == 8)
            {
                columnBegin = 1;
                columnEnd = 1;
            }
        }
        ///Jumping
        else if (velocity.y != 0.0f)
        {
            columnBegin = 6;
            columnEnd = 6;
        }
        ///Idle
        else if (velocity.x < 0.5f && velocity.x > -0.5f)
        {
            columnBegin = 0;
            columnEnd = 0;
        }
        ///Turning left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && velocity.x > 0.0f)
        {
            columnBegin = 5;
            columnEnd = 5;
        }
        ///Turning right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && velocity.x < 0.0f)
        {
            columnBegin = 5;
            columnEnd = 5;
        }
        ///Running
        else
        {
            columnBegin = 1;
            columnEnd = 4;
        }
    }
    ///Big
    else if (isBig == 1)
    {
        ///Manage invincibility
        if (invincibilityTimer == -1.0f)
        {
            row = 1;
        }
        else if (invincibilityTimer != -1.0f)
        {
            if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 0)
            {
                row = 1;
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 1)
            {
                row = 7;
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 2)
            {
                if (level == 11)
                {
                    if (area == 0)
                    {
                        row = 9;
                    }
                    else if (area == 1)
                    {
                        row = 13;
                    }
                }
                else
                {
                    row = 9;
                }
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 3)
            {
                if (level == 11)
                {
                    if (area == 0)
                    {
                        row = 11;
                    }
                    else if (area == 1)
                    {
                        row = 15;
                    }
                }
                else
                {
                    row = 11;
                }
            }
        }

        ///Grabbing onto flagpole
        if (isGrabbing == 1)
        {
            columnBegin = 8;
            columnEnd = 9;
        }
        ///Using a warp pipe
        else if (isWarping == 1)
        {
            if (warps[currentWarp].direction == 1 || warps[currentWarp].direction == 2)
            {
                columnBegin = 0;
                columnEnd = 0;
            }
            else if (warps[currentWarp].direction == 3 || warps[currentWarp].direction == 4)
            {
                columnBegin = 1;
                columnEnd = 1;
            }
        }
        else if (isWarping == 2)
        {
            if (warps[warpIndex].direction == 1 || warps[warpIndex].direction == 2 || warps[warpIndex].direction == 5 || warps[warpIndex].direction == 6)
            {
                columnBegin = 0;
                columnEnd = 0;
            }
            else if (warps[warpIndex].direction == 3 || warps[warpIndex].direction == 4 || warps[warpIndex].direction == 7 || warps[warpIndex].direction == 8)
            {
                columnBegin = 1;
                columnEnd = 1;
            }
        }
        ///Ducking
        else if (isCrouching)
        {
            columnBegin = 7;
            columnEnd = 7;
        }
        ///Jumping
        else if (velocity.y != 0.0f)
        {
            columnBegin = 6;
            columnEnd = 6;
        }
        ///Idle
        else if (velocity.x < 0.5f && velocity.x > -0.5f)
        {
            columnBegin = 0;
            columnEnd = 0;
        }
        ///Turning left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && velocity.x > 0.0f)
        {
            columnBegin = 5;
            columnEnd = 5;
        }
        ///Turning right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && velocity.x < 0.0f)
        {
            columnBegin = 5;
            columnEnd = 5;
        }
        ///Running
        else
        {
            columnBegin = 1;
            columnEnd = 4;
        }
    }
    ///Fire
    else if (isBig == 2)
    {
        ///Manage invincibility
        if (invincibilityTimer == -1.0f)
        {
            row = 5;
        }
        else if (invincibilityTimer != -1.0f)
        {
            if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 0)
            {
                row = 5;
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 1)
            {
                row = 7;
            }
            else if ((int)(invincibilityTimer * 10 + 0.5) % 4 == 2)
            {
                if (level == 11)
                {
                    if (area == 0)
                    {
                        row = 9;
                    }
                    else if (area == 1)
                    {
                        row = 13;
                    }
                }
                else
                {
                    row = 9;
                }
            }
            else if ((int)(invincibilityTimer + 0.5) % 4 == 3)
            {
                if (level == 11)
                {
                    if (area == 0)
                    {
                        row = 11;
                    }
                    else if (area == 1)
                    {
                        row = 15;
                    }
                }
                else
                {
                    row = 11;
                }
            }
        }

        ///Grabbing onto flagpole
        if (isGrabbing == 1)
        {
            columnBegin = 8;
            columnEnd = 9;
        }
        ///Using a warp pipe
        else if (isWarping == 1)
        {
            if (warps[currentWarp].direction == 1 || warps[currentWarp].direction == 2)
            {
                columnBegin = 0;
                columnEnd = 0;
            }
            else if (warps[currentWarp].direction == 3 || warps[currentWarp].direction == 4)
            {
                columnBegin = 1;
                columnEnd = 1;
            }
        }
        else if (isWarping == 2)
        {
            if (warps[warpIndex].direction == 1 || warps[warpIndex].direction == 2 || warps[warpIndex].direction == 5 || warps[warpIndex].direction == 6)
            {
                columnBegin = 0;
                columnEnd = 0;
            }
            else if (warps[warpIndex].direction == 3 || warps[warpIndex].direction == 4 || warps[warpIndex].direction == 7 || warps[warpIndex].direction == 8)
            {
                columnBegin = 1;
                columnEnd = 1;
            }
        }
        ///Fireball
        else if (fireballTimer > 0.0f)
        {
            columnBegin = 1;
            columnEnd = 1;
        }
        ///Ducking
        else if (isCrouching)
        {
            columnBegin = 7;
            columnEnd = 7;
        }
        ///Jumping
        else if (velocity.y != 0.0f)
        {
            columnBegin = 6;
            columnEnd = 6;
        }
        ///Idle
        else if (velocity.x < 0.5f && velocity.x > -0.5f)
        {
            columnBegin = 0;
            columnEnd = 0;
        }
        ///Turning left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && velocity.x > 0.0f)
        {
            columnBegin = 5;
            columnEnd = 5;
        }
        ///Turning right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && velocity.x < 0.0f)
        {
            columnBegin = 5;
            columnEnd = 5;
        }
        ///Running
        else
        {
            columnBegin = 1;
            columnEnd = 4;
        }
    }

    ///Determine the direction that Mario's animation should face based on velocity
    if (isGrabbing == 0)
    {
        if (velocity.x > 0.0f)
        {
            faceRight = true;
        }
        else if (velocity.x < 0.0f)
        {
            faceRight = false;
        }
    }
    ///if the player has hopped off the flag pole and is walking towards the castle
    else if (isGrabbing == 2)
    {
        faceRight = true;
    }

    ///Manage animation speed
    ///Running
    if (velocity.x > 0.5f || velocity.x < -0.5f)
    {
        ///The speed in which the player's animation updates will always follow their speed
        switchTime = 50 / abs(velocity.x);
        ///Set a min and max for animation switch time
        if (switchTime < 0.075f)
        {
            switchTime = 0.075f;
        }
        else if (switchTime > 0.2f)
        {
            switchTime = 0.2f;
        }
    }
    ///Grabbing onto flagpole
    else if (isGrabbing == 1)
    {
        ///Do the slide animation
        if (body.getPosition().y < flagpoles[0].GetPosition().y - body.getSize().y / 2.0f)
        {
            switchTime = 0.25f;
        }
        else
        {
            switchTime = 0.0f;
        }
    }
    ///Any single-framed animation
    else
    {
        ///Don't switch
        switchTime = 0.0f;
    }
    animation.SetSwitchtime(switchTime);

    ///Apply animation
    animation.Update(row, columnBegin, columnEnd, deltaTime, faceRight);
    sprite.setTextureRect(animation.uvRect);
    if (isBig > 0 && !isCrouching)
    {
        sprite.setPosition(body.getPosition());
    }
    else
    {
        sprite.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y - 16.0f));
    }
}

///Manual animation updater
void Player::SetRow (int index, float deltaTime)
{
    row = index;
    animation.Update(row, columnBegin, columnEnd, deltaTime, faceRight);
    sprite.setTextureRect(animation.uvRect);
}

///Manual animation updater
void Player::SetColumn (int indexBegin, int indexEnd, float deltaTime)
{
    columnBegin = indexBegin;
    columnEnd = indexEnd;
    animation.Update(row, columnBegin, columnEnd, deltaTime, faceRight);
    sprite.setTextureRect(animation.uvRect);
}

///Take damage
void Player::Hurt(int type)
{
    ///Reset crouch
    if (isCrouching)
    {
        body.setSize(sf::Vector2f(24.0f, 62.0f));
        body.setOrigin(body.getSize() / 2.0f);
        body.move(0.0f, -16.0f);
        isCrouching = false;
    }

    ///Basic damage (from enemies)
    if (type == 0)
    {
        ///If player does not have grace
        if (graceTimer <= 0)
        {
            ///Do damage animation using the pauseCounter variable
            ///Basically the same as powering up, just in reverse
            if (isBig == 2)
            {
                pauseCounter.before = 2;
                pauseCounter.after = 0;
                pauseCounter.switchTimer = 1.0f;
                isBig -= 2;
                audioManager.PlayAudio("pipe");
            }
            else
            {
                ///Mario is already small, and the damage kills him
                if (isBig == 0)
                {
                    velocity.x = 0.0f;
                    deathTimer = 0.0f;
                    ///Mario launches upwards after death
                    velocity.y = -sqrt(981.0f * jumpHeight / 2);
                    row = 9;
                    ///Set music
                    requestedMusic = "death";
                }
                ///Mario is big, and the damage brings him bad down to small
                else if (isBig > 0)
                {
                    pauseCounter.before = isBig;
                    pauseCounter.after = isBig - 1;
                    pauseCounter.switchTimer = 1.0f;
                    ///Play power-down sound, which is the same as using a warp pipe
                    audioManager.PlayAudio("pipe");
                }
                isBig--;
            }
            //graceTimer = 2;
        }
    }
    ///Instant death damage
    else if (type == 1)
    {
        row = 9;
        isBig = -1;
        velocity.x = 0.0f;
        deathTimer = 0.0f;
        velocity.y = -sqrt(981.0f * jumpHeight / 2);
        requestedMusic = "death";
    }
}

///At the start of the level (in "void StartLevel(int level)" from "game.cpp"), this function will reset the player's states and position
void Player::Reset()
{
    ///Reset ghost effect from grace timer and collision with castle door
    sprite.setFillColor(sf::Color(255, 255, 255, 255));
    ///Set position to the start of the level
    if (isBig < 1)
    {
        body.setPosition(sf::Vector2f(64.0f, 576.0f));
    }
    else
    {
        body.setPosition(sf::Vector2f(64.0f, 560.0f));
    }
    sprite.setPosition(body.getPosition());
    isGrabbing = 0;
    grabDistance = 0.0f;
    grabTimer = 0.0f;
    streak = 1;
    graceTimer = 0.0f;
    shellInvincibility = -1;
    deathTimer = -1.0f;
    faceRight = true;
    fireballTimer = 0.0f;
    invincibilityTimer = -1.0f;
}

///Function for drawing the player's sprite to the screen
void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
