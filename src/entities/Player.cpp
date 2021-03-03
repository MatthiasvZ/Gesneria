#include "Player.h"

Player::Player(float x, float y, float hitboxSize)
    : Entity(x, y, hitboxSize)
{
    updateVertices();
    frictionF = 0.1f;
}

void Player::updateVertices()
{
    vertices =
    {
        this->x - hitboxSize, this->y - hitboxSize, 0.0f, 0.0f,
        this->x - hitboxSize, this->y + hitboxSize, 0.0f, 1.0f,
        this->x + hitboxSize, this->y + hitboxSize, 1.0f, 1.0f,
        this->x + hitboxSize, this->y - hitboxSize, 1.0f, 0.0f
    };
}

Player::~Player()
{

}
