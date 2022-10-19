#pragma once
#include "yaObject.h"

namespace ya
{
	class Missile : public Object
	{
    private:
        float   m_fSpeed;

        float      m_fDir; // 이동 방향(라디안)
        Vector2    m_vDir;

    public:
        virtual void Tick() override;
        virtual void Render(HDC _dc) override;

    public:
        Missile();
        ~Missile();
	};
}
