#include "SpriteComponent.h"

USING_NS_CC;

SpriteComponent::SpriteComponent()
{}

SpriteComponent::SpriteComponent(ComponentId id, cocos2d::Sprite * sprite)
	:m_SpriteId(id), m_Sprite(sprite)
{}

void SpriteComponent::VSetSprite(cocos2d::Sprite * sprite)
{
	m_Sprite = sprite;
}
