#ifndef STAGE_H
#define STAGE_H

#include "Petroleum.h"
#include "Player.h"

class Stage
{
    public:
        Stage(PT::Input* p_Inputs);
        virtual void update(float deltaTime);
        virtual ~Stage();

    protected:
        Player player;

        PT::Shader shader;
        PT::VertexBuffer playerVbo;
        PT::IndexBuffer spriteIbo;
        PT::VertexArray spriteVao;
        //PT::VertexBuffer backgroundVbo;
        //PT::IndexBuffer backgroundIbo;
        //PT::VertexArray backgroundVao;
        PT::Input* p_Inputs;

        unsigned int state;
        float deltaTime;
        float aspectRatio;

        void updatePositions();
        void draw();

    private:
};

#endif // STAGE_H
