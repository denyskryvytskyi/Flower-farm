#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "cocos2d.h"
#include "ActorComponent.h"

class SpriteComponent : public ActorComponent
{
private:
    ComponentId m_SpriteId;
    cocos2d::Sprite* m_Sprite;
public:
    SpriteComponent();
    SpriteComponent(ComponentId id, cocos2d::Sprite* sprite);
    //
    void VUpdate(void) override;
    ComponentId VGetComponentId(void) const override;
    //
    void SetSprite(cocos2d::Sprite* sprite);
    cocos2d::Sprite* GetSprite();
};

#endif // !__SPRITE_COMPONENT_H__
