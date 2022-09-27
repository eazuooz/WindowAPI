#pragma once
#include "yaObject.h"

namespace ya
{
	class Monster : public Object
	{

        public:
            Monster();
            ~Monster();

            virtual void Tick() override;
            virtual void Render(HDC hdc) override;

        private:
            float mSpeed;
            float mShotTime;
	};
}
