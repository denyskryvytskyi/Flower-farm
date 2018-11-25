#include "LabelComponent.h"

void LabelComponent::UpdateLabel(float dt)
{
	cocos2d::log("Coins count: %d", p_PlayerCoins->GetCoinsCount());

	m_LabelText = std::to_string(p_PlayerCoins->GetCoinsCount());
	m_Label->setString(m_LabelText);
}

LabelComponent::LabelComponent(cocos2d::Vec2 position, std::string text, PlayerCoinsComponent * playerCoins, int labelTextSize)
	: m_LabelPosition(position), m_LabelText(text), p_PlayerCoins(playerCoins), m_LabelTextSize(labelTextSize)
{
	m_Label = cocos2d::Label::createWithSystemFont(m_LabelText, "Arial", m_LabelTextSize);
	m_Label->setPosition(m_LabelPosition);
}

cocos2d::Label * LabelComponent::GetLabel()
{
	return m_Label;
}

void LabelComponent::VUpdate()
{
	cocos2d::Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(LabelComponent::UpdateLabel), this, 1.0f, false);
}
