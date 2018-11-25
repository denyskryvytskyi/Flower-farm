#include "Actor.h"

Actor::Actor()
	:m_LastComponentId(-1)
{
}

Actor::Actor(ActorId m_ActorId)
	:m_ActorId(m_ActorId), m_LastComponentId(-1)
{
}

void Actor::AddComponent(StrongActorComponentPtr pComponent)
{
	m_Components[++m_LastComponentId] = pComponent;
}
