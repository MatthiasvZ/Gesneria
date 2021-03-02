#include "Stage1.h"

Stage1::Stage1(PT::Input* p_Inputs) : Stage(p_Inputs)
{
    GLEC(glClearColor(0.0977f, 0.1680f, 0.3008f, 1.0f));
}

void Stage1::update(float deltaTime)
{

    draw();
}

Stage1::~Stage1()
{

}
