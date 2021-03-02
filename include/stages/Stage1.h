#ifndef STAGE1_H
#define STAGE1_H

#include "Stage.h"


class Stage1 : public Stage
{
    public:
        Stage1(PT::Input* p_Inputs);
        void update(float deltaTime) override;
        ~Stage1();

    protected:

    private:
};

#endif // STAGE1_H
