#include "SpriteComponent.h"


SpriteComponent::SpriteComponent()
{}

SpriteComponent::SpriteComponent(ComponentId id, cocos2d::Sprite* sprite)
    :m_SpriteId(id),
    m_Sprite(sprite)
{}

void SpriteComponent::VUpdate(void)
{
}

ComponentId SpriteComponent::VGetComponentId(void) const
{
    return m_SpriteId;
}

void SpriteComponent::SetSprite(cocos2d::Sprite* sprite)
{
    m_Sprite = sprite;
}

cocos2d::Sprite* SpriteComponent::GetSprite()
{
    return m_Sprite;
}
