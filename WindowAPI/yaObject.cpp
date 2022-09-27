#include "yaObject.h"
#include "yaComponent.h"

namespace ya
{
    Object::Object()
        : mPos{}
        , mScale{}
    {
        mComponents.resize((UINT)eComponentType::End);
    }

    Object::~Object()
    {
        for (Component* component : mComponents)
        {
            if (nullptr == component)
                continue;

            delete component;
        }
    }

    void Object::Tick()
    {
        for (Component* component : mComponents)
        {
            if (nullptr == component)
                continue;

            component->Tick();
        }
    }

    void Object::Render(HDC hdc)
    {
        for (Component* component : mComponents)
        {
            if (nullptr == component)
                continue;

            component->Render(hdc);
        }
    }
    void Object::AddComponent(Component* component)
    {
        mComponents[(UINT)component->GetType()] = component;
        component->mOwner = this;
    }
}