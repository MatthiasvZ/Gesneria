#include "Stage.h"

Stage::Stage(PT::Input* p_Inputs)
    : shader(PT_SHADER_XYUV_M),
      vertices(std::vector<float>()), vbo(vertices), ibo(std::vector<unsigned char>()),
      p_Inputs(p_Inputs),
      state(0), deltaTime(0.0f)
{

}

void Stage::update(float deltaTime)
{

}

void Stage::draw()
{
    PT::drawVA(vao, ibo, shader);
}

Stage::~Stage()
{
    vao.remove();
    vbo.remove();
    ibo.remove();
}
