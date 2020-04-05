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

enum MouseButtons
{
    Left,
    Right,
    Middle
};

cocos2d::Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

    auto layer = MainScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}



bool MainScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    LayerColor* _bgColor = LayerColor::create(Color4B(70, 200, 70, 255));
    this->addChild(_bgColor, -10);

    ActorFactory factory;

    StrongActorPtr coins(new Actor());

    ComponentId nextComponentId = coins->GetNextComponentId();
    auto pinfo = AutoPolygon::generatePolygon("coin.png");
    Sprite* sprite = Sprite::create(pinfo);
    sprite->setScale(0.1);
    sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    sprite->setPosition(Vec2(20, resolution::designResolutionSize.height - 20));

    std::shared_ptr<SpriteComponent> spriteComponent(new SpriteComponent(nextComponentId, sprite));
    factory.AddComponentToActor(coins, std::static_pointer_cast<ActorComponent>(spriteComponent));
    this->addChild(coins->GetComponent<SpriteComponent>(spriteComponent->VGetComponentId())->GetSprite(), 5);

    nextComponentId = coins->GetNextComponentId();
    PlayerCoinsComponent& playerCoinsComponent = PlayerCoinsComponent::Instance();

    int startPlayerCoinsCount = 150;
    playerCoinsComponent.AddCoins(startPlayerCoinsCount);

    nextComponentId = coins->GetNextComponentId();
    LabelComponent* labelComponent = new LabelComponent(Vec2(100, resolution::designResolutionSize.height - 35), std::to_string(startPlayerCoinsCount), &playerCoinsComponent, 20);
    factory.AddComponentToActor(coins, std::static_pointer_cast<ActorComponent>(std::shared_ptr<LabelComponent>(labelComponent)));
    labelComponent->VUpdate();
    this->addChild(labelComponent->GetLabel(), 5);

    SnakeGenerator* snakeGenerator(new SnakeGenerator());
    snakeGenerator->VUpdate();
    this->addChild(snakeGenerator);

    auto listener = EventListenerMouse::create();

    listener->onMouseDown = [&](cocos2d::Event* event) {

        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        if ((int)mouseEvent->getMouseButton() == MouseButtons::Right)
        {
            if (playerCoinsComponent.GetCoinsCount() >= playerCoinsComponent.GetFlowerPrice())
            {
                playerCoinsComponent.RemoveCoins(playerCoinsComponent.GetFlowerPrice());

                StrongActorPtr flower(new Actor());

                int nextComponentId = flower->GetLastComponentId() + 1;

                auto inf = AutoPolygon::generatePolygon("Chamomile.png");
                Sprite* spr = Sprite::create(inf);
                spr->setPosition(mouseEvent->getLocation().x, resolution::designResolutionSize.height - mouseEvent->getLocation().y);
                spr->setAnchorPoint(Vec2(0.5, 0.5));
                spr->setScale(0.5);

                std::shared_ptr<SpriteComponent> spriteComponent(new SpriteComponent(nextComponentId, spr));
                factory.AddComponentToActor(flower, std::static_pointer_cast<ActorComponent>(spriteComponent));

                nextComponentId = flower->GetLastComponentId() + 1;
                std::shared_ptr<CoinsStashComponent> flowerComponent(new CoinsStashComponent(nextComponentId, &playerCoinsComponent));
                factory.AddComponentToActor(flower, std::static_pointer_cast<ActorComponent>(flowerComponent));
                flowerComponent->VUpdate();

                this->addChild(flower->GetComponent<SpriteComponent>(spriteComponent->VGetComponentId())->GetSprite(), 0);
            }
            m_PlayerCoinsCount = playerCoinsComponent.GetCoinsCount();
        }
    };

    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

    this->scheduleUpdate();

    return true;
}