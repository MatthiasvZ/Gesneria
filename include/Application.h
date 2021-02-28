#ifndef APPLICATION_H
#define APPLICATION_H

#include "Petroleum.h"
#include "Menu.h"

#define APP_STATE_MENU 0
#define APP_STATE_AWAITING_CLOSURE 1

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
};

#endif // APPLICATION_H
