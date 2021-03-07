#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"


class Bullet : public Entity
{
    public:
        Bullet(float x, float y, float hitboxSize, float uOffset = 0.0f, float vOffset = 0.0f);

        virtual inline float getUOffset() const { return uOffset; }
        virtual inline float getVOffset() const { return vOffset; }

        virtual ~Bullet();

    protected:
        float uOffset;
        float vOffset;

    private:
};

#endif // BULLET_H
