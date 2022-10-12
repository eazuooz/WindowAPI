#include "yaObject.h"
#include "yaComponent.h"
#include "yaSceneManager.h"
#include "yaScene.h"

namespace ya
{
    /*void Object::Destory(Object* object)
    {
        if (object != nullptr)
            object->mDead = true;
    }*/

    //void Object::Release()
    //{
    //    Scene* scene = SceneManager::GetPlayScene();
    //    SceneObjects objects = scene->GetObjects();
    //    
    //    for (size_t y = 0; y < _COLLIDER_LAYER; y++)
    //    {
    //        for (LayerObjectsIter iter = objects[y].begin()
    //            ; iter != objects[y].end(); iter++)
    //        {
    //            if ((*iter)->IsDead() == true)
    //            {
    //                iter = objects[y].erase(iter);
    //            }
    //        }
    //    }
    //}

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

    void Object::AddComponent(Component* component)
    {
        mComponents[(UINT)component->GetType()] = component;
        component->mOwner = this;
    }

}