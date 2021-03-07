#include "Stage1.h"

Stage1::Stage1(PT::Window* p_Window) : Stage(p_Window)
{
    GLEC(glClearColor(0.0977f, 0.1680f, 0.3008f, 1.0f));
}
#include <iostream>
void Stage1::update(float deltaTime)
{
    Stage::update(deltaTime);

    for (unsigned int i {1}; i < 25; ++i)
    {
        if (stageTimer > i + 1 && stageProgression ==  i - 1)
        {
            ++stageProgression;
            if (i % 2)
                for (float i = M_PI; i < 2 * M_PI + 0.01; i += M_PI / 24)
                    p_Bullets->push_back(Bullet1(0.0f, 0.0f, i));
            else
                for (float i = M_PI + M_PI / 48; i < 2 * M_PI - M_PI / 48 + 0.01; i += M_PI / 24)
                    p_Bullets->push_back(Bullet1(0.0f, 0.0f, i));
        }
    }
}

Stage1::~Stage1()
{

}
