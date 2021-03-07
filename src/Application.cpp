#include "Application.h"
#include "Stage1.h"

Application::Application(PT::Window* p_Window)
    : p_Window(p_Window), state(APP_STATE_MENU), menu(p_Window), stage(nullptr)
{
    //ctor
}

void Application::update(float deltaTime)
{
    switch (state)
    {
        case APP_STATE_MENU:
            menu.update(deltaTime);
            switch (menu.getState())
            {
                case WAITING_TO_CLOSE:
                    state = APP_STATE_AWAITING_CLOSURE;
                    break;
                case WAITING_TO_BEGIN_GAME:
                    state = APP_STATE_LOADING_STAGE_1;
                    break;
            }
            break;

        case APP_STATE_LOADING_STAGE_1:
            stage = new Stage1(p_Window);
            state = APP_STATE_STAGE_1;
            break;

        case APP_STATE_STAGE_1: [[fallthrough]];
        case APP_STATE_STAGE_2: [[fallthrough]];
        case APP_STATE_STAGE_3: [[fallthrough]];
        case APP_STATE_STAGE_4: [[fallthrough]];
        case APP_STATE_STAGE_5: [[fallthrough]];
        case APP_STATE_STAGE_6:
            stage->update(deltaTime);
            break;
    }
}

Application::~Application()
{
    delete stage;
}
