#pragma once

#ifndef __ACTOR_COMPONENT_H__
#define __ACTOR_COMPONENT_H__

#include "cocos2d.h"
#include "Actor.h"

typedef std::shared_ptr<Actor> StrongActorPtr;

// Abstract class that contain common information for every component
class ActorComponent : public cocos2d::Node
{
	friend class ActorFactory;
protected:
	StrongActorPtr m_pOwner;
public:
	virtual ~ActorComponent(void) { }

	// This function should be overridden by the class.
	virtual void VUpdate() = 0;
	// This function should be overridden by the class.
	virtual ComponentId VGetComponentId(void) const = 0;
private:
	void SetOwner(StrongActorPtr pOwner) { m_pOwner = pOwner; }
};

#endif // __ACTOR_COMPONENT_H__
