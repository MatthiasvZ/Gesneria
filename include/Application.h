#ifndef APPLICATION_H
#define APPLICATION_H

#include "Petroleum.h"
#include "Menu.h"
#include "Stage.h"

#define APP_STATE_MENU             0
#define APP_STATE_AWAITING_CLOSURE 1
#define APP_STATE_LOADING_STAGE_1  2
#define APP_STATE_STAGE_1          3
#define APP_STATE_LOADING_STAGE_2  4
#define APP_STATE_STAGE_2          5
#define APP_STATE_LOADING_STAGE_3  6
#define APP_STATE_STAGE_3          7
#define APP_STATE_LOADING_STAGE_4  8
#define APP_STATE_STAGE_4          9
#define APP_STATE_LOADING_STAGE_5  10
#define APP_STATE_STAGE_5          11
#define APP_STATE_LOADING_STAGE_6  12
#define APP_STATE_STAGE_6          13

class Application
{
    public:
        Application(PT::Input* p_Inputs);

        void update(float deltaTime);
        inline unsigned int getState() { return state; }

        ~Application();

    protected:

    private:
        PT::Input* p_Inputs;
        unsigned int state;

        Menu menu;
        Stage* stage;
};

#endif // APPLICATION_H
