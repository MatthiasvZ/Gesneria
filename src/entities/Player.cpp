#include "Player.h"

Player::Player(float x, float y, float hitboxSize)
    : Entity(x, y, hitboxSize), lives(5), invincibilityTimer(0.0f)
{
    frictionF = 0.1f;
}

void Player::updatePosL(float deltaTime)
{
    updatePosL(deltaTime, angle);
}

void Player::updatePosL(float deltaTime, float newAngle)
{
    angle = newAngle;
    const float movementX = speedCap * deltaTime * cos(angle);
    const float movementY = speedCap * deltaTime * sin(angle);

    x += movementX;
    y += movementY;

    if (x < -1.0f)
        x = -1.0f;
    if (x > 1.0f)
        x = 1.0f;
    if (y < -1.0f)
        y = -1.0f;
    if (y > 1.0f)
        y = 1.0f;
}

void Player::update(float deltaTime)
{
    invincibilityTimer -= deltaTime;
}

#include <iostream>
void Player::hit()
{
    if (invincibilityTimer > 0.0f)
        return;

    --lives;
    std::cerr << "The player has been hit! Remaining lives: " << lives << std::endl;
    invincibilityTimer = 2.0f;
}

Player::~Player()
{

}
