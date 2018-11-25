#ifndef __ACTOR_FACTORY_H__
#define __ACTOR_FACTORY_H__

#include "cocos2d.h"
#include "Actor.h"
#include "ActorComponent.h"

typedef std::shared_ptr<Actor> StrongActorPtr;

// Class for creating actors and adding components to actor
class ActorFactory
{
	ActorId m_LastActorId;
public:
	ActorFactory(void);
	StrongActorPtr CreateActor();
	void AddComponentToActor(StrongActorPtr acto, StrongActorComponentPtr component);
private:
	ActorId GetNextActorId(void) { ++m_LastActorId; return m_LastActorId; }
};

#endif // __ACTOR_FACTORY_H__
