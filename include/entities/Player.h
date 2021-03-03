#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
    public:
        Player(float x, float y, float hitboxSize);
        void updateVertices() override;

        inline float getFullSpeedCap() { return 0.5f; }
        inline float getShiftSpeedCap() { return 0.2f; }
        inline float getMaxAcceleration() { return 250.0f; }

        virtual ~Player();

    protected:

    private:

};

#endif // PLAYER_H
