#pragma once

#ifndef __LABEL_COMPONENT_H__
#define __LABEL_COMPONENT_H__

#include "ActorComponent.h"
#include "PlayerCoinsComponent.h"

/*
/ Class is responsible for the logic of the labels: 
/ - "the number of coins"
/ - "not enough coins"
/ - "the end of the game"
*/
class LabelComponent : public ActorComponent
{
private:
	cocos2d::Label* m_Label;
	std::string m_LabelText;
	int m_LabelTextSize;
	ComponentId m_LabelId;
	cocos2d::Vec2 m_LabelPosition;
	PlayerCoinsComponent* p_PlayerCoins;
public:
	// Constructors
	LabelComponent() {}
	LabelComponent(cocos2d::Vec2 position, std::string text, PlayerCoinsComponent* playerCoins, int labelTextSize);
	LabelComponent(cocos2d::Vec2 position, std::string text) : m_LabelPosition(position), m_LabelText(text) {}

	cocos2d::Label* GetLabel();
	
	void VUpdate();
	virtual ComponentId VGetComponentId(void) const { return m_LabelId; }

public:
	void UpdateLabel(float dt);
};
#endif // __LABEL_COMPONENT_H__