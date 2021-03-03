#include "Stage.h"

#include "../assets/spriteAtlas.png.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#define SPRITE_ATLAS_SLOT 0

// TODO remove
#define SPRITE_ATLAS_LENGTH MENU_ATLAS_LENGTH
#define SPRITE_ATLAS MENU_ATLAS

Stage::Stage(PT::Input* p_Inputs)
    : player(0.0f, -0.5f, 0.05f),
      shader(PT_SHADER_XYUV_M),
      playerVbo(*player.getVertices()), spriteIbo(PT::tIndsSquares<unsigned char>(1)),
      p_Inputs(p_Inputs),
      state(0), deltaTime(0.0f), aspectRatio(0.0f)
{
    spriteVao.addBuffer(playerVbo, shader.getLayout());
}

void Stage::update(float deltaTime)
{

}

void Stage::updatePositions()
{
    player.setSpeedCap(p_Inputs->leftShiftHeld ? player.getShiftSpeedCap() : player.getFullSpeedCap());

    int dx = 0;
    int dy = 0;

    dy += p_Inputs->wHeld;
    dy -= p_Inputs->sHeld;
    dx += p_Inputs->dHeld;
    dx -= p_Inputs->aHeld;

    if (dx == 0 && dy == 0)
    {
        player.setAcceleration(0.0f);
        player.updatePosL(deltaTime);
    }
    else
    {
        player.setAcceleration(player.getMaxAcceleration());
        player.updatePosL(deltaTime, atan2(dy, dx) - atan2(0.0f, 1.0f));
    }


    playerVbo.updateData(*player.getVertices());
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

Stage::~Stage()
{
    playerVbo.remove();
    spriteVao.remove();
    spriteIbo.remove();
}
