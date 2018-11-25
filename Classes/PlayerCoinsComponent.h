#ifndef __PLAYER_COINS_COMPONENT_H__
#define __PLAYER_COINS_COMPONENT_H__

#include "ActorComponent.h"

/* 
/ Singleton class
/ Responsible for the logic of coins: adding and removing coins
*/

class PlayerCoinsComponent : public ActorComponent
{
	friend class CoinsStashComponent;
private:
	long m_CoinsCount;
	int m_FlowerPrice;
	ComponentId m_PlayerCoinsId;

public:
	static PlayerCoinsComponent& Instance()
	{
		static PlayerCoinsComponent playerCoins;
		playerCoins.m_FlowerPrice = 50;
		return playerCoins;
	}

	long GetCoinsCount() const { return m_CoinsCount; }
	virtual void VUpdate(void) {}
	virtual ComponentId VGetComponentId(void) const { return m_PlayerCoinsId; }

	// Adding and removing coins
	void AddCoins(int coins);
	void RemoveCoins(int coins);

	int GetFlowerPrice() const { return m_FlowerPrice; }
private:
	PlayerCoinsComponent() :m_CoinsCount(0){};
	~PlayerCoinsComponent() {};

	// Prohibit copying
	PlayerCoinsComponent(PlayerCoinsComponent const&) = delete;
	PlayerCoinsComponent& operator= (PlayerCoinsComponent const&) = delete;
};

#endif // __PLAYER_COINS_COMPONENT_H__
