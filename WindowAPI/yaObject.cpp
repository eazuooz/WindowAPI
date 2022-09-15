#include "yaObject.h"


namespace ya
{
    Object::Object()
    {
    }

    Object::~Object()
    {
    }

    void Object::Render(HDC hdc)
    {
        Rectangle(hdc
            , int(mPos.x - mScale.x / 2.f)
            , int(mPos.y - mScale.y / 2.f)
            , int(mPos.x + mScale.x / 2.f)
            , int(mPos.y + mScale.y / 2.f));
    }
}