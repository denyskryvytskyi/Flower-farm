#ifndef __PLAYER_COINS_COMPONENT_H__
#define __PLAYER_COINS_COMPONENT_H__

#include "ActorComponent.h"

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
    //
    void VUpdate(void) override;
    ComponentId VGetComponentId(void) const override;
    //
    long GetCoinsCount() const;
    void AddCoins(int coins);
    void RemoveCoins(int coins);
    //
    int GetFlowerPrice() const;

private:
    PlayerCoinsComponent();
    //
    PlayerCoinsComponent(PlayerCoinsComponent const&) = delete;
    PlayerCoinsComponent& operator=(PlayerCoinsComponent const&) = delete;
};

#endif // !__PLAYER_COINS_COMPONENT_H__