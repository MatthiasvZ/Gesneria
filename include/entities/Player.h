#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
    public:
        Player(float x, float y, float hitboxSize);

        void updatePosL(float deltaTime) override;
        void updatePosL(float deltaTime, float newAngle) override;

        void update(float deltaTime);
        void hit();

        inline float getFullSpeedCap() { return 0.5f; }
        inline float getShiftSpeedCap() { return 0.2f; }
        inline float getMaxAcceleration() { return 250.0f; }

        virtual ~Player();

    protected:

    private:
        unsigned int lives;
        float invincibilityTimer;
};

#endif // PLAYER_H
