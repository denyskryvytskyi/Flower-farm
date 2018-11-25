#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
class ActorComponent;

typedef unsigned long ComponentId;
typedef unsigned long ActorId;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;

/*
/ Class for the every game object
/ Consist of the components depending of game object
*/
class Actor
{
	friend class ActorFactory;
private:
	typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;

	ActorId m_ActorId; // unique id for the actor
	ActorComponents m_Components; // all components this actor has
	ComponentId m_LastComponentId; // last component id in map m_Components
public:
	Actor();
	Actor(ActorId m_ActorId);

	ComponentId GetLastComponentId() { return m_LastComponentId; }

	// template function for retrieving components
	template <class CommonType>
	std::shared_ptr<CommonType> GetComponent(ComponentId id)
	{
		ActorComponents::iterator findIt = m_Components.find(id);
		if (findIt != m_Components.end())
		{
			StrongActorComponentPtr pBase(findIt->second);

			// cast to subclass version of the pointer
			std::shared_ptr<CommonType> pSub(std::static_pointer_cast<CommonType>(pBase));
			return pSub; // retur pointer
		}
		else
		{
			return std::shared_ptr<CommonType>();
		}
	}

private:
	// This is called by the ActorFactory; no one else should be adding components.
	void AddComponent(StrongActorComponentPtr pComponent);
};

#endif // __ACTOR_H__
