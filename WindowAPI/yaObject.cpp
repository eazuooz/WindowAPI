#include "yaObject.h"
#include "yaComponent.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
    Object::Object(Object& other)
        : mComponents{ }
        , mPos{ other.mPos }
        , mScale{ other.mScale }
        , mbDead(false)
    {
        mComponents.resize((UINT)eComponentType::End);
        for (Component* component : other.mComponents)
        {
            if (nullptr == component)
                continue;

            Component* newComp = CreateComponent(component);
            AddComponent(newComp);
        }
    }

    Object::Object()
        : mPos{}
        , mScale{}
        , mbDead(false)
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

    Component* Object::CreateComponent(Component* component)
    {
        Component* newComp = nullptr;
        switch (component->GetType())
        {
        case eComponentType::Animator:
        {
            Animator* other = dynamic_cast<Animator*>(component);
            newComp = new Animator(*other);
        }
        break;

        case eComponentType::Collider:
        {
            Collider* other = dynamic_cast<Collider*>(component);
            newComp = new Collider(*other);
        }
        break;

        case eComponentType::Rigidbody:
        {
            Rigidbody* other = dynamic_cast<Rigidbody*>(component);
            newComp = new Rigidbody(*other);
        }
        break;

        default:
            break;
        }

        return newComp;
    }

    void Object::AddComponent(Component* component)
    {
        mComponents[(UINT)component->GetType()] = component;
        component->mOwner = this;
    }

}