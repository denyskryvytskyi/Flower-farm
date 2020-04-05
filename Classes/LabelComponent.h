#ifndef __LABEL_COMPONENT_H__
#define __LABEL_COMPONENT_H__

#include "ActorComponent.h"
#include "PlayerCoinsComponent.h"

class LabelComponent : public ActorComponent
{
private:
    int m_LabelTextSize;
    float m_TimeUpdateInterval;
    //
    std::string m_LabelText;
    //
    ComponentId m_LabelId;
    PlayerCoinsComponent* p_PlayerCoins;
    cocos2d::Label* m_Label;
    cocos2d::Vec2 m_LabelPosition;

public:
    LabelComponent(cocos2d::Vec2 position, std::string text, PlayerCoinsComponent* playerCoins, int labelTextSize);
    LabelComponent(cocos2d::Vec2 position, std::string text);
    //
    cocos2d::Label* GetLabel();
    //
    void VUpdate() override;
    ComponentId VGetComponentId(void) const override { return m_LabelId; }

public:
    void UpdateLabel(float dt);
};
#endif // !__LABEL_COMPONENT_H__