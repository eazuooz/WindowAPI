#pragma once
#include "yaObject.h"

namespace ya
{
    class Image;
	class Monster : public Object
	{

        public:
            Monster();
            ~Monster();

            virtual void Tick() override;
            virtual void Render(HDC hdc) override;

        private:
            Image* mImage;
            
	};
}
