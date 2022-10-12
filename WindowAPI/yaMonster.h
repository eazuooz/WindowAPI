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

            virtual void OnCollisionEnter(Collider* other) override;
            virtual void OnCollisionStay(Collider* other) override;
            virtual void OnCollisionExit(Collider* other) override;

        private:
            Image* mImage;
            
	};
}
