#pragma once
#include "yaObject.h"

namespace ya
{
	class Missile : public Object
	{
    private:
        float   m_fSpeed;

    public:
        virtual void Tick() override;
        virtual void Render(HDC _dc) override;

    public:
        Missile();
        ~Missile();
	};
}
