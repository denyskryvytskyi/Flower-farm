#include "SnakeGenerator.h"
#include "SnakeComponent.h"

void SnakeGenerator::GenerateSnake(float dt)
{
	// Snake
	// Create a static PhysicsBody
	auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(32.0f, 32.0f), cocos2d::PhysicsMaterial(0.0f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);

	// Sprite
	auto pinfoSnake = cocos2d::AutoPolygon::generatePolygon("SnakeCell.png");
	cocos2d::Sprite* spriteSnake = cocos2d::Sprite::create(pinfoSnake);
	spriteSnake->setScale(0.5);
	spriteSnake->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	spriteSnake->setPosition(cocos2d::Vec2(100, 100));

	// Sprite will use physicsBody
	spriteSnake->addComponent(physicsBody);

	// SnakeComponent
	SnakeComponent* snake = new SnakeComponent((int)designResolutionSize.height, (int)designResolutionSize.width, 32, 10);
	snake->Setup();
	snake->SetHeadSprite(spriteSnake);
	snake->VUpdate();

	this->addChild(snake);
}

void SnakeGenerator::VUpdate()
{
	// generate snake every five seconds
	cocos2d::Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SnakeGenerator::GenerateSnake), this, m_TimeSnakeGeneration, false);
}
