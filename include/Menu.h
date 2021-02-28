#ifndef MENU_H
#define MENU_H

#include "Petroleum.h"

// States
#define NONE 0
#define MAIN_SCREEN 1
#define OPTION_MENU 2
#define WAITING_TO_BEGIN_GAME 3
#define WAITING_TO_CLOSE 4


class Menu
{
    public:
        Menu(PT::Input* p_Inputs);

        void update(float deltaTime);
        inline unsigned int getState() { return state; }

        ~Menu();

    protected:

    private:
        PT::Shader shader;
        std::vector<float> vertices;
        PT::VertexBuffer vbo;
        PT::IndexBuffer ibo;
        PT::VertexArray vao;
        PT::Input* p_Inputs;

        PT::Texture tex_menuAtlas;

        float vp[4];
        float aspectRatio;
        unsigned int state;
        unsigned int nextState;
        float deltaTime;
        unsigned int animationPlaying;
        unsigned int ActiveHighlight;

        unsigned int mouseOn();
        void animation_MoveOffscreen();
        void animation_MoveIn();
        void animation_Highlight(unsigned int option);
        void animation_UnHighlight(unsigned int option);
};

#endif // MENU_H
