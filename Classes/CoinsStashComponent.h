#pragma once

#ifndef __COINS_STASH_COMPONENT_H__
#define __COINS_STASH_COMPONENT_H__

#include "cocos2d.h"
#include "ActorComponent.h"
#include "PlayerCoinsComponent.h"

// Class is responsible for the game logic of the flower actor: stash coins
class CoinsStashComponent : public ActorComponent
{
private:
	int m_TimeCoinsGeneration;
	PlayerCoinsComponent* p_PlayerCoins;
	short m_CoinsStashTime;
	ComponentId m_FlowerId;
	
public:
	CoinsStashComponent();
	CoinsStashComponent(ComponentId id);
	CoinsStashComponent(ComponentId id, PlayerCoinsComponent* coins);

	virtual void VUpdate(void);
	virtual ComponentId VGetComponentId() const { return m_FlowerId; }
	void StashCoin();
private:
	// Every 3 seconds generate 5 coins
	void GenerateCoins(float dt);
};

#endif // __COINS_STASH_COMPONENT_H__
