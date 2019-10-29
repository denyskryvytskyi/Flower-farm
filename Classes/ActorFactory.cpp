#include "ActorFactory.h"

USING_NS_CC;

ActorFactory::ActorFactory(void)
	:m_LastActorId(0)
{}

StrongActorPtr ActorFactory::CreateActor()
{
	StrongActorPtr actor(new Actor(m_LastActorId));
	GetNextActorId();
	return actor;
}

void ActorFactory::AddComponentToActor(StrongActorPtr actor, StrongActorComponentPtr component)
{
	component->SetOwner(actor);
	actor->AddComponent(component);
}