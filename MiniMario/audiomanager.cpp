#include "header.h"
#include "audiomanager.h"

AudioManager::AudioManager()
{
    //ctor
}

AudioManager::~AudioManager()
{
    //dtor
}

void AudioManager::LoadAudio()
{
    ///Sound effects
    breakBlockBuffer.loadFromFile("audio/breakBlock.wav");
    breakBlockSound.setBuffer(breakBlockBuffer);
    bumpBuffer.loadFromFile("audio/bump.wav");
    bumpSound.setBuffer(bumpBuffer);
    coinBuffer.loadFromFile("audio/coin.wav");
    coinSound.setBuffer(coinBuffer);
    fireballBuffer.loadFromFile("audio/fireball.wav");
    fireballSound.setBuffer(fireballBuffer);
    fireworksBuffer.loadFromFile("audio/fireworks.wav");
    fireworksSound.setBuffer(fireworksBuffer);
    flagpoleBuffer.loadFromFile("audio/flagpole.wav");
    flagpoleSound.setBuffer(flagpoleBuffer);
    jumpBuffer.loadFromFile("audio/jump.wav");
    jumpSound.setBuffer(jumpBuffer);
    kickBuffer.loadFromFile("audio/kick.wav");
    kickSound.setBuffer(kickBuffer);
    oneUpBuffer.loadFromFile("audio/oneUp.wav");
    oneUpSound.setBuffer(oneUpBuffer);
    pauseBuffer.loadFromFile("audio/pause.wav");
    pauseSound.setBuffer(pauseBuffer);
    pipeBuffer.loadFromFile("audio/pipe.wav");
    pipeSound.setBuffer(pipeBuffer);
    powerupBuffer.loadFromFile("audio/powerup.wav");
    powerupSound.setBuffer(powerupBuffer);
    powerupAppearsBuffer.loadFromFile("audio/powerupAppears.wav");
    powerupAppearsSound.setBuffer(powerupAppearsBuffer);
}

void AudioManager::PlayAudio(string sound)
{
    if (sound == "breakBlock")
    {
        breakBlockSound.play();
    }
    else if (sound == "bump")
    {
        bumpSound.play();
    }
    else if (sound == "coin")
    {
        coinSound.play();
    }
    else if (sound == "fireball")
    {
        fireballSound.play();
    }
    else if (sound == "fireworks")
    {
        fireworksSound.play();
    }
    else if (sound == "flagpole")
    {
        flagpoleSound.play();
    }
    else if (sound == "jump")
    {
        jumpSound.play();
    }
    else if (sound == "kick")
    {
        kickSound.play();
    }
    else if (sound == "oneUp")
    {
        oneUpSound.play();
    }
    else if (sound == "pause")
    {
        pauseSound.play();
    }
    else if (sound == "pipe")
    {
        pipeSound.play();
    }
    else if (sound == "powerup")
    {
        powerupSound.play();
    }
    else if (sound == "powerupAppears")
    {
        powerupAppearsSound.play();
    }
}
