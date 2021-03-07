#include "Stage.h"

#include "../assets/spriteAtlas.png.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#define SPRITE_ATLAS_SLOT 0

Stage::Stage(PT::Window* p_Window)
    : shader(PT_SHADER_XYUV_M),
      tex_SpriteAtlas(SPRITE_ATLAS_LENGTH, SPRITE_ATLAS, 0, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR),
      player(0.0f, -0.5f, 0.01f),
      spriteVbo(std::vector<float>()), spriteIbo(PT::tIndsSquares<unsigned int>(1 + ENTITY_LIMIT_ENEMIES + ENTITY_LIMIT_BULLETS)),
      p_Window(p_Window),
      deltaTime(0.0f), aspectRatio(0.0f),
      stageProgression(0), stageTimer(0.0f)
{
    tex_SpriteAtlas.setIndexSize(64.0f);

    spriteVao.addBuffer(spriteVbo, shader.getLayout());

    p_Enemies = new std::vector<Enemy>();
    p_Bullets = new std::vector<Bullet>();
}

void Stage::update(float deltaTime)
{
    this->deltaTime = deltaTime;
    stageTimer += deltaTime;
    updatePositions();
    player.update(deltaTime);
    collisionCheck();
    removeDeadEntities();
    updateVertices();
    draw();
}

void Stage::updatePositions()
{
    player.setSpeedCap(p_Window->getKey(GLFW_KEY_LEFT_SHIFT) ? player.getShiftSpeedCap() : player.getFullSpeedCap());

    int dx = 0;
    int dy = 0;

    dy += p_Window->getKey(GLFW_KEY_W);
    dy -= p_Window->getKey(GLFW_KEY_S);
    dx += p_Window->getKey(GLFW_KEY_D);
    dx -= p_Window->getKey(GLFW_KEY_A);

    if (dx != 0 || dy != 0)
        player.updatePosL(deltaTime, atan2(dy, dx));

    for (auto& bullet : *p_Bullets)
        bullet.updatePosL(deltaTime);
}

void Stage::collisionCheck()
{
    for (const auto& bullet : *p_Bullets)
        if (player.isTouching(bullet))
            player.hit();
}

void Stage::updateVertices()
{
    // Initialise with the player's vertices
    std::vector<float> spriteVertices =
    {
        player.getX() - player.getHitboxSize(), player.getY() - player.getHitboxSize(), tex_SpriteAtlas.getU1(0.0f), tex_SpriteAtlas.getV1(0.0f),
        player.getX() - player.getHitboxSize(), player.getY() + player.getHitboxSize(), tex_SpriteAtlas.getU2(0.0f), tex_SpriteAtlas.getV2(0.0f),
        player.getX() + player.getHitboxSize(), player.getY() + player.getHitboxSize(), tex_SpriteAtlas.getU3(0.0f), tex_SpriteAtlas.getV3(0.0f),
        player.getX() + player.getHitboxSize(), player.getY() - player.getHitboxSize(), tex_SpriteAtlas.getU4(0.0f), tex_SpriteAtlas.getV4(0.0f),
    };

    // Add those of the bullets
    auto bulletCount = activeBullets();
    spriteVertices.reserve(4 * 4 * bulletCount);
    for (const auto& elt : *p_Bullets)
    {
        if (!elt.isActive())
            continue;

        spriteVertices.push_back(elt.getX() - elt.getHitboxSize());
        spriteVertices.push_back(elt.getY() - elt.getHitboxSize());
        spriteVertices.push_back(tex_SpriteAtlas.getU1(elt.getUOffset()));
        spriteVertices.push_back(tex_SpriteAtlas.getV1(elt.getVOffset()));

        spriteVertices.push_back(elt.getX() - elt.getHitboxSize());
        spriteVertices.push_back(elt.getY() + elt.getHitboxSize());
        spriteVertices.push_back(tex_SpriteAtlas.getU2(elt.getUOffset()));
        spriteVertices.push_back(tex_SpriteAtlas.getV2(elt.getVOffset()));

        spriteVertices.push_back(elt.getX() + elt.getHitboxSize());
        spriteVertices.push_back(elt.getY() + elt.getHitboxSize());
        spriteVertices.push_back(tex_SpriteAtlas.getU3(elt.getUOffset()));
        spriteVertices.push_back(tex_SpriteAtlas.getV3(elt.getVOffset()));

        spriteVertices.push_back(elt.getX() + elt.getHitboxSize());
        spriteVertices.push_back(elt.getY() - elt.getHitboxSize());
        spriteVertices.push_back(tex_SpriteAtlas.getU4(elt.getUOffset()));
        spriteVertices.push_back(tex_SpriteAtlas.getV4(elt.getVOffset()));
    }
    spriteVbo.updateData(spriteVertices);
    spriteIbo.updateData(PT::tIndsSquares<unsigned int>(1 + activeEnemies() + bulletCount));
    // std::cerr << "vbo.size = " << spriteVertices.size() << ", ibo.size = " << (1 + activeEnemies() + bulletCount) * 6 << std::endl;
}

#define ELT_IS_ONSCREEN !(elt.getX() < -1.1f || elt.getX() > 1.1f || elt.getY() < -1.1f || elt.getY() > 1.1f)

void Stage::removeDeadEntities()
{
    if (p_Enemies->size() > ENTITY_LIMIT_ENEMIES)
    {
        std::vector<Enemy>* p_NewEnemies = new std::vector<Enemy>();
        p_NewEnemies->reserve(enemiesOnScreen());

        for (const auto& elt : *p_Enemies)
            if (elt.isActive() && ELT_IS_ONSCREEN)
                p_NewEnemies->push_back(elt);

        delete p_Enemies;
        p_Enemies = p_NewEnemies;

        if (p_Enemies->size() > ENTITY_LIMIT_ENEMIES)
            fprintf(stderr, "WARNING: Reached entity cap for enemies!\n");
    }

    if (p_Bullets->size() > ENTITY_LIMIT_BULLETS)
    {
        std::vector<Bullet>* p_NewBullets = new std::vector<Bullet>();
        p_NewBullets->reserve(bulletsOnScreen());

        for (const auto& elt : *p_Bullets)
            if (elt.isActive() && ELT_IS_ONSCREEN)
                p_NewBullets->push_back(elt);

        delete p_Bullets;
        p_Bullets = p_NewBullets;

        if (p_Bullets->size() > ENTITY_LIMIT_BULLETS)
            fprintf(stderr, "WARNING: Reached entity cap for bullets!\n");
    }
}

void Stage::draw()
{
    float vp[4];
    GLEC(glGetFloatv(GL_VIEWPORT, vp));
    if (aspectRatio != vp[2] / vp[3])
    {
        aspectRatio = vp[2] / vp[3];
        glm::mat4 scaleMat = glm::scale(glm::vec3(1.0f / aspectRatio, 1.0f, 1.0f));
        shader.setUniformMat4f("u_Mat", scaleMat);
    }
    PT::drawVA(spriteVao, spriteIbo, shader);
}

unsigned long Stage::activeEnemies()
{
    unsigned long result = 0;
    for (const auto& elt : *p_Enemies)
        result += elt.isActive();
    return result;
}

unsigned long Stage::activeBullets()
{
    unsigned long result = 0;
    for (const auto& elt : *p_Bullets)
        result += elt.isActive();
    return result;
}

unsigned long Stage::enemiesOnScreen()
{
    unsigned long result = 0;
    for (const auto& elt : *p_Enemies)
        result += elt.isActive() && ELT_IS_ONSCREEN;
    return result;
}

unsigned long Stage::bulletsOnScreen()
{
    unsigned long result = 0;
    for (const auto& elt : *p_Bullets)
        result += elt.isActive() && ELT_IS_ONSCREEN;
    return result;
}

Stage::~Stage()
{
    spriteVao.remove();
    spriteVbo.remove();
    spriteIbo.remove();

    delete p_Enemies;
    delete p_Bullets;
}
