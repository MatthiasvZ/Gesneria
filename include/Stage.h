#ifndef STAGE_H
#define STAGE_H

#include "Petroleum.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletTypes.h"
#include "Enemy.h"

#define ENTITY_LIMIT_ENEMIES 100
#define ENTITY_LIMIT_BULLETS 200

class Stage
{
    public:
        Stage(PT::Window* p_Window);
        virtual void update(float deltaTime);
        virtual ~Stage();

    protected:

        PT::Shader shader;

        PT::TextureAtlas tex_SpriteAtlas;
        Player player;
        PT::VertexBuffer spriteVbo;
        PT::IndexBuffer spriteIbo;
        PT::VertexArray spriteVao;
        PT::Window* p_Window;

        std::vector<Enemy>* p_Enemies;
        std::vector<Bullet>* p_Bullets;

        float deltaTime;
        float aspectRatio;

        unsigned int stageProgression;
        float stageTimer;

        void updatePositions();
        void collisionCheck();
        void updateVertices();
        void removeDeadEntities();
        void draw();

        unsigned long activeEnemies();
        unsigned long activeBullets();
        unsigned long enemiesOnScreen();
        unsigned long bulletsOnScreen();

    private:
};

#endif // STAGE_H
