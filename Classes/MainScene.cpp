#include "MainScene.h"
#include "ActorFactory.h"
#include "CoinsStashComponent.h"
#include "SpriteComponent.h"
#include "PlayerCoinsComponent.h"
#include "LabelComponent.h"
#include "ResolutionManager.h"
#include "SnakeComponent.h"
#include "SnakeGenerator.h"

USING_NS_CC;

cocos2d::Scene* MainScene::createScene()
{
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

	auto layer = MainScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

enum MouseButtons{Left, Right, Middle}; // Mouse buttons: 0 - left, 1 - right, 2 - middle

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	// BG
	LayerColor *_bgColor = LayerColor::create(Color4B(70, 200, 70, 255));
	this->addChild(_bgColor, -10);
	
	// GameObjects maps
	//std::map<ActorId, ActorFlower> flowers;
	ActorFactory factory;

	// CoinActor
	StrongActorPtr coins(new Actor());
	
	// SpriteComponent for ActorCoins
	ComponentId nextComponentId = coins->GetLastComponentId() + 1;
	auto pinfo = AutoPolygon::generatePolygon("coin.png");
	Sprite* sprite = Sprite::create(pinfo);
	sprite->setScale(0.1);
	sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
	sprite->setPosition(Vec2(20, designResolutionSize.height - 20));

	std::shared_ptr<SpriteComponent> spriteComponent(new SpriteComponent(nextComponentId, sprite));
	factory.AddComponentToActor(coins, std::static_pointer_cast<ActorComponent>(spriteComponent));
	this->addChild(coins->GetComponent<SpriteComponent>(spriteComponent->VGetComponentId())->VGetSprite(), 5);

	// PlayerCoinsComponent for ActorCoins
	nextComponentId = coins->GetLastComponentId() + 1;
	PlayerCoinsComponent& playerCoinsComponent = PlayerCoinsComponent::Instance();
	
	int startPlayerCoinsCount = 150;
	playerCoinsComponent.AddCoins(startPlayerCoinsCount);

	// LabelComponent for ActorCoins
	nextComponentId = coins->GetLastComponentId() + 1;
	LabelComponent*  lableComponent = new LabelComponent(Vec2(100, designResolutionSize.height - 35), std::to_string(startPlayerCoinsCount), &playerCoinsComponent, 20);
	factory.AddComponentToActor(coins, std::static_pointer_cast<ActorComponent>(std::shared_ptr<LabelComponent>(lableComponent)));
	lableComponent->VUpdate();	
	this->addChild(lableComponent->GetLabel(), 5);

	//// Label not enough coins
	//m_NotEnoughCoins = Label::createWithSystemFont("Not enough coins!", "Arial", 40);
	//m_NotEnoughCoins->setPosition(Vec2(designResolutionSize.width / 2, designResolutionSize.height / 2));
	//m_NotEnoughCoins->setTextColor(Color4B(255, 0, 0, 255));
	//m_NotEnoughCoins->setName("NotEnoughCoins");
	//this->addChild(m_NotEnoughCoins, 10);
	
	SnakeGenerator* snakeGenerator(new SnakeGenerator());
	snakeGenerator->VUpdate();
	this->addChild(snakeGenerator);

	// Listeners
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [&](cocos2d::Event* event) {

		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		if ((int)mouseEvent->getMouseButton() == MouseButtons::Right)
		{
			// Если достаточно монет - можно посадить цветочек
			if (playerCoinsComponent.GetCoinsCount() >= playerCoinsComponent.GetFlowerPrice())
			{
				playerCoinsComponent.RemoveCoins(playerCoinsComponent.GetFlowerPrice());
				// Flower
				StrongActorPtr flower(new Actor());

				int nextComponentId = flower->GetLastComponentId() + 1;

				// Set SpriteComponent
				auto inf = AutoPolygon::generatePolygon("Chamomile.png");
				Sprite* spr = Sprite::create(inf);
				spr->setPosition(mouseEvent->getLocation().x, designResolutionSize.height - mouseEvent->getLocation().y);
				spr->setAnchorPoint(Vec2(0.5, 0.5));
				spr->setScale(0.5);

				std::shared_ptr<SpriteComponent> spriteComponent(new SpriteComponent(nextComponentId, spr));
				factory.AddComponentToActor(flower, std::static_pointer_cast<ActorComponent>(spriteComponent));

				// Set FlowerComponent
				nextComponentId = flower->GetLastComponentId() + 1;
				std::shared_ptr<CoinsStashComponent> flowerComponent(new CoinsStashComponent(nextComponentId, &playerCoinsComponent));
				factory.AddComponentToActor(flower, std::static_pointer_cast<ActorComponent>(flowerComponent));
				flowerComponent->VUpdate(); // Stash coins

				this->addChild(flower->GetComponent<SpriteComponent>(spriteComponent->VGetComponentId())->VGetSprite(), 0);
			}
			m_PlayerCoinsCount = playerCoinsComponent.GetCoinsCount();
		}
	};

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	////add contact event listener
	//auto contactListener = EventListenerPhysicsContact::create();
	//contactListener->onContactBegin = CC_CALLBACK_1(MouseScene::onContactBegin, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();

	return true;
}

void MainScene::onContactBegin(cocos2d::PhysicsContact &contact)
{}

void MainScene::update(float dt)
{
	//cocos2d::log("MouseSceneUpdateMethod");
	//if (m_PlayerCoinsCount >= 50)
	//{
	//	m_NotEnoughCoins->setVisible(false);
	//}
	//else
	//{
	//	m_NotEnoughCoins->setVisible(true);
	//}
}