#include "Application.h"

Application::Application(PT::Input* p_Inputs)
    : p_Inputs(p_Inputs), state(APP_STATE_MENU), menu(p_Inputs)
{
    //ctor
}

void Application::update(float deltaTime)
{
    switch (state)
    {
        case APP_STATE_MENU:
            menu.update(deltaTime);
            if (menu.getState() == WAITING_TO_CLOSE)
                state = APP_STATE_AWAITING_CLOSURE;
            break;
    }
}

Application::~Application()
{
    //dtor
}
