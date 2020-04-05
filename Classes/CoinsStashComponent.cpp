#include "CoinsStashComponent.h"

USING_NS_CC;

CoinsStashComponent::CoinsStashComponent()
	:m_CoinsStashTime(3), m_TimeCoinsGeneration(5)
{}

CoinsStashComponent::CoinsStashComponent(ComponentId id)
	:m_FlowerId(id), m_CoinsStashTime(3), m_TimeCoinsGeneration(5)
{}

CoinsStashComponent::CoinsStashComponent(ComponentId id, PlayerCoinsComponent* coins)
	: m_FlowerId(id), m_CoinsStashTime(3), p_PlayerCoins(coins), m_TimeCoinsGeneration(5)
{}

void CoinsStashComponent::VUpdate(void)
{
	Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(CoinsStashComponent::GenerateCoins), this, 3.0f, false);
}

void CoinsStashComponent::GenerateCoins(float dt)
{
	p_PlayerCoins->AddCoins(m_TimeCoinsGeneration);
	int c = p_PlayerCoins->GetCoinsCount();
}

void CoinsStashComponent::StashCoin()
{
	int delay = m_CoinsStashTime;

	// Create listener
	auto listener = EventListenerCustom::create("Flower stash coin event", [=](EventCustom* event) {
		int coinsCount = 20;
	});
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 2);

	// Triggered listener
	EventCustom event("Flower stash coin event");

	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}