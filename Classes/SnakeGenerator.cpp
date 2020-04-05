#include "SnakeGenerator.h"
#include "SnakeComponent.h"

void SnakeGenerator::GenerateSnake(float dt)
{
    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(32.0f, 32.0f), cocos2d::PhysicsMaterial(0.0f, 1.0f, 0.0f));
    physicsBody->setDynamic(false);

    auto pinfoSnake = cocos2d::AutoPolygon::generatePolygon("SnakeCell.png");
    SpritePtr spriteSnake = cocos2d::Sprite::create(pinfoSnake);
    spriteSnake->setScale(0.5);
    spriteSnake->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    spriteSnake->setPosition(cocos2d::Vec2(100, 100));

    spriteSnake->addComponent(physicsBody);

    SnakeComponent* snake = new SnakeComponent((int)resolution::designResolutionSize.height, (int)resolution::designResolutionSize.width, 32, 10);
    snake->Setup();
    snake->SetHeadSprite(spriteSnake);
    snake->VUpdate();

    this->addChild(snake);
}

void SnakeGenerator::VUpdate()
{
    cocos2d::Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SnakeGenerator::GenerateSnake), this, m_TimeSnakeGeneration, false);
}
