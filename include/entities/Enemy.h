#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
    public:
        Enemy(float x, float y, float hitboxSize);

        virtual ~Enemy();

    protected:

    private:
};

#endif // ENEMY_H
