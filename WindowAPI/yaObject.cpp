#include "yaObject.h"
#include "yaComponent.h"

namespace ya
{
    Object::Object()
        : mPos{}
        , mScale{}
    {
    }

    Object::~Object()
    {
    }

    void Object::Tick()
    {
        for (Component* component : mComponents)
        {
            component->Tick();
        }
    }

    void Object::Render(HDC hdc)
    {
        for (Component* component : mComponents)
        {
            component->Render(hdc);
        }
    }
    void Object::AddComponent(Component* component)
    {
        mComponents.push_back(component);
    }
}