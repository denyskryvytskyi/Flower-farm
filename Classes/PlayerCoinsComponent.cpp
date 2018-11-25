#include "PlayerCoinsComponent.h"

void PlayerCoinsComponent::AddCoins(int coins)
{
	m_CoinsCount += coins;
}

void PlayerCoinsComponent::RemoveCoins(int coins)
{
	m_CoinsCount -= coins;
}
