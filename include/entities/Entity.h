#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>
#include <vector>


class Entity
{
    public:
        Entity(float x, float y, float hitboxSize);

        inline float getX() const { return x; }
        inline float getY() const { return y; }
        inline float getHitboxSize() const { return hitboxSize; }
        inline std::vector<float>* getVertices() { return &vertices; }
        inline float distanceTo(Entity b) const { return sqrt(pow(this->x - b.getX(), 2) + pow(this->y - b.getY(), 2)); }
        inline bool isTouching(Entity b) const { return distanceTo(b) < this->hitboxSize + b.getHitboxSize(); }

        void moveTo(float x, float y);
        void moveRelative(float x, float y);
        virtual void updatePosL(float deltaTime);
        virtual void updatePosL(float deltaTime, float newAngle);
        void updatePosQ(float deltaTime);
        void updatePosQ(float deltaTime, float newAngle);

        inline void setAcceleration(float acceleration) { this->acceleration = acceleration; }
        inline void setVelocity(float velocity) { this->velocity = velocity; }
        inline void setAngle(float angle) { this->angle = angle; }
        inline void setSpeedCap(float speedCap) { this->speedCap = speedCap; }

        inline bool isActive() const { return active; }

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

        bool active;

    private:
};

#endif // ENTITY_H
