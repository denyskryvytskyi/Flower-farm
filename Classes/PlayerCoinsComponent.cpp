#include "PlayerCoinsComponent.h"

long PlayerCoinsComponent::GetCoinsCount() const
{
    return m_CoinsCount;
}

void PlayerCoinsComponent::VUpdate(void)
{
}

ComponentId PlayerCoinsComponent::VGetComponentId(void) const
{
    return m_PlayerCoinsId;
}

void PlayerCoinsComponent::AddCoins(int coins)
{
    m_CoinsCount += coins;
}

void PlayerCoinsComponent::RemoveCoins(int coins)
{
    m_CoinsCount -= coins;
}

int PlayerCoinsComponent::GetFlowerPrice() const
{
    return m_FlowerPrice;
}

PlayerCoinsComponent::PlayerCoinsComponent()
    :m_CoinsCount(0)
{
}
