#include "header.h"
#include "animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
    uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
}

Animation::~Animation()
{
    //dtor
}

void Animation::Update(int row, int columnBegin, int columnEnd, float deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (switchTime != 0.0f)
    {
        if (totalTime >= switchTime)
        {
            totalTime -= switchTime;
            currentImage.x++;
            if (currentImage.x < columnBegin)
            {
                currentImage.x = columnBegin;
            }
            else if (currentImage.x >= imageCount.x || currentImage.x > columnEnd)
            {
                currentImage.x = columnBegin;
            }
        }
    }
    else
    {
        currentImage.x = columnBegin;
    }

    uvRect.top = currentImage.y * uvRect.height;

    if (faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}

void Animation::SetTexture(sf::Texture* texture)
{
    uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
    uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
}
