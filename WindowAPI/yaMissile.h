#pragma once
#include "yaObject.h"

namespace ya
{
	class Missile : public Object
	{
    private:
        float   m_fSpeed;

        float      m_fDir; // �̵� ����(����)
        Vector2    m_vDir;

    public:
        virtual void Tick() override;
        virtual void Render(HDC _dc) override;

    public:
        Missile();
        ~Missile();
	};
}
