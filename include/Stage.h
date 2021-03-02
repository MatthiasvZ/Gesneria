#ifndef STAGE_H
#define STAGE_H

#include "Petroleum.h"

class Stage
{
    public:
        Stage(PT::Input* p_Inputs);
        virtual void update(float deltaTime);
        virtual ~Stage();

    protected:
        PT::Shader shader;
        std::vector<float> vertices;
        PT::VertexBuffer vbo;
        PT::IndexBuffer ibo;
        PT::VertexArray vao;
        //PT::VertexBuffer backgroundVbo;
        //PT::IndexBuffer backgroundIbo;
        //PT::VertexArray backgroundVao;
        PT::Input* p_Inputs;

        unsigned int state;
        float deltaTime;

        void draw();

    private:
};

#endif // STAGE_H
