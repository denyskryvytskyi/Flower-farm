#ifndef __ACTOR_COMPONENT_H__
#define __ACTOR_COMPONENT_H__

#include "cocos2d.h"
#include "Actor.h"

typedef std::shared_ptr<Actor> StrongActorPtr;

class ActorComponent : public cocos2d::Node
{
    friend class ActorFactory;

protected:
    StrongActorPtr m_pOwner;

public:
    virtual void VUpdate() = 0;
    virtual ComponentId VGetComponentId(void) const = 0;

private:
    void SetOwner(const StrongActorPtr pOwner) { m_pOwner = pOwner; }
};

#endif // !__ACTOR_COMPONENT_H__
