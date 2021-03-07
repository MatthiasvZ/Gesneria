#ifndef BULLET_TYPES_H
#define BULLET_TYPES_H

#include "Bullet.h"

class Bullet1 : public Bullet
{
    public:
        Bullet1(float x, float y, float angle = M_PI + M_PI / 2) : Bullet(x, y, 0.02f, 1.0f, 0.0f)
        {
            setAcceleration(5000.0f);
            setSpeedCap(1.0f);
            setAngle(angle);
        }
};

#endif // BULLET_TYPES_H
