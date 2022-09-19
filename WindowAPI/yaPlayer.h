#pragma once
#include "yaObject.h"

namespace ya
{
    class Player : public Object
    {
    public:
        Player();
        ~Player();

        virtual void Tick() override;

    private:
        float mSpeed;
        float mShotTime;
    };
}
