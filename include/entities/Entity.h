#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>
#include <vector>


class Entity
{
    public:
        Entity(float x, float y, float hitboxSize);

        inline float getX() { return x; }
        inline float getY() { return y; }
        inline float getHitboxSize() { return hitboxSize; }
        inline std::vector<float>* getVertices() { return &vertices; }
        inline bool isTouching(Entity b) { return abs(this->x - b.getX()) + abs(this->y - b.getY()) < this->hitboxSize + b.getHitboxSize(); }

        void moveTo(float x, float y);
        void moveRelative(float x, float y);
        void updatePosL(float deltaTime);
        void updatePosL(float deltaTime, float newAngle);
        void updatePosQ(float deltaTime);
        void updatePosQ(float deltaTime, float newAngle);

        inline void setAcceleration(float acceleration) { this->acceleration = acceleration; }
        inline void setVelocity(float velocity) { this->velocity = velocity; }
        inline void setAngle(float angle) { this->angle = angle; }
        inline void setSpeedCap(float speedCap) { this->speedCap = speedCap; }

    protected:
        float x;
        float y;
        float hitboxSize;
        float acceleration;
        float velocity;
        float angle;
        float speedCap;
        float frictionF; // technically 1/2 * A * cw
        constexpr static float ρAir = 1.0f;
        std::vector<float> vertices;
        virtual void updateVertices();

    private:
};

#endif // ENTITY_H
