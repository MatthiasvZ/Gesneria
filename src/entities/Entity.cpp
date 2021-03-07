#include "Entity.h"

Entity::Entity(float x, float y, float hitboxSize)
    : x(x), y(y), hitboxSize(hitboxSize), acceleration(0.0f), velocity(0.0f), angle(0.0f), speedCap(0.0f), frictionF(0.0f), active(true)
{

}

void Entity::moveTo(float x, float y)
{
    this->x = x;
    this->y = y;
    updateVertices();
}

void Entity::moveRelative(float x, float y)
{
    this->x += x;
    this->y += y;
    updateVertices();
}

void Entity::updateVertices()
{
    vertices =
    {
        this->x - hitboxSize, this->y - hitboxSize, 0.0f, 0.0f,
        this->x - hitboxSize, this->y + hitboxSize, 0.0f, 1.0f,
        this->x + hitboxSize, this->y + hitboxSize, 1.0f, 1.0f,
        this->x + hitboxSize, this->y - hitboxSize, 1.0f, 0.0f
    };
}
#include <iostream>
void Entity::updatePosL(float deltaTime)
{
    updatePosL(deltaTime, angle);
}

void Entity::updatePosL(float deltaTime, float newAngle)
{
    angle = newAngle;
    const float movementX = speedCap * deltaTime * cos(angle);
    const float movementY = speedCap * deltaTime * sin(angle);

    x += movementX;
    y += movementY;

    updateVertices();
}

void Entity::updatePosQ(float deltaTime)
{
    updatePosQ(deltaTime, angle);
}

void Entity::updatePosQ(float deltaTime, float newAngle)
{
    const float movementX = 0.5f * acceleration * deltaTime * deltaTime * cos(newAngle) + velocity * deltaTime * cos(angle);
    const float movementY = 0.5f * acceleration * deltaTime * deltaTime * sin(newAngle) + velocity * deltaTime * sin(angle);
    angle = atan2(movementY, movementX);

    x += movementX;
    y += movementY;

    //std::cerr << "angle = " << angle << std::endl;
    //std::cerr << "vel = " << velocity << ", std::abs(vel) = " << std::abs(velocity) << std::endl;
    const float friction = ρAir * frictionF * velocity * std::abs(velocity);
    velocity = std::max(std::min(velocity + acceleration * deltaTime - friction, speedCap), -speedCap);

    updateVertices();
}
