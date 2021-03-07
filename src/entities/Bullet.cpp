#include "Bullet.h"

Bullet::Bullet(float x, float y, float hitboxSize, float uOffset, float vOffset)
    : Entity(x, y, hitboxSize), uOffset(uOffset), vOffset(vOffset)
{
    //ctor
}

Bullet::~Bullet()
{
    //dtor
}
