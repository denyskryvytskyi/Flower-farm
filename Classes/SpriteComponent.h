#pragma once

#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "cocos2d.h"
#include "ActorComponent.h"

//
// Responsible for the sprites of the game object
//
class SpriteComponent : public ActorComponent
{
private:
	ComponentId m_SpriteId;
	cocos2d::Sprite* m_Sprite;
public:
	SpriteComponent();
	SpriteComponent(ComponentId id, cocos2d::Sprite* sprite);

	virtual void VUpdate(void) {}
	virtual ComponentId VGetComponentId(void) const { return m_SpriteId; }
	virtual void VSetSprite(cocos2d::Sprite* sprite);
	virtual cocos2d::Sprite* VGetSprite() { return m_Sprite; }
};

#endif // __SPRITE_COMPONENT_H__
