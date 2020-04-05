#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"

class ActorComponent;

typedef unsigned long ComponentId;
typedef unsigned long ActorId;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;

class Actor
{
    friend class ActorFactory;

private:
    typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;
    //
    ActorId m_ActorId;
    ActorComponents m_Components;
    ComponentId m_LastComponentId;

public:
    Actor();
    Actor(ActorId m_ActorId);
    //
    ComponentId GetLastComponentId() { return m_LastComponentId; }
    ComponentId GetNextComponentId() { return m_LastComponentId + 1; }
    //
    template <class CommonType>
    std::shared_ptr<CommonType> GetComponent(ComponentId id)
    {
        ActorComponents::iterator findIt = m_Components.find(id);
        if (findIt != m_Components.end())
        {
            StrongActorComponentPtr pBase(findIt->second);

            std::shared_ptr<CommonType> pSub(std::static_pointer_cast<CommonType>(pBase));
            return pSub;
        }
        else
        {
            return std::shared_ptr<CommonType>();
        }
    }

private:
    void AddComponent(StrongActorComponentPtr pComponent);
};

#endif // !__ACTOR_H__
