#ifndef __ACTOR_FACTORY_H__
#define __ACTOR_FACTORY_H__

#include "cocos2d.h"
#include "Actor.h"
#include "ActorComponent.h"

typedef std::shared_ptr<Actor> StrongActorPtr;

class ActorFactory
{
    ActorId m_LastActorId;

public:
    ActorFactory(void);
    StrongActorPtr CreateActor();
    void AddComponentToActor(StrongActorPtr acto, StrongActorComponentPtr component);

private:
    ActorId GetNextActorId(void);
};

#endif // !__ACTOR_FACTORY_H__
