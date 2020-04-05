#include "SnakeComponent.h"

SnakeComponent::SnakeComponent(int heightMap, int widthMap, int cellSize, int snakeSpeed)
    : m_CellSpriteSize(cellSize),
    m_SnakeSpeed(snakeSpeed),
    m_SnakeCellsCount(0)
{
    m_Map = new Matrix<sCellPosition>(heightMap, widthMap);
}

SnakeComponent::~SnakeComponent()
{
    delete m_Map;
    delete m_HeadSprite;
    for (auto tailSprite : m_TailSprites)
    {
        delete tailSprite;
    }
    m_TailSprites.clear();
}

void SnakeComponent::Setup()
{
    srand(time(0));
    int x = 100 + rand() % (m_Map->rows() - 100);
    int y = 100 + rand() % (m_Map->cols() - 100);
    m_HeadPosition = { x, y };

    m_MoveDirection = (EDirection)(rand() % 4);
}

void SnakeComponent::SnakeMoving(float dt)
{
    const EDirection currentDir = m_MoveDirection;
    const int boundaryValue = m_CellSpriteSize;
    bool validDirection = true;

    do {
        m_MoveDirection = static_cast<EDirection>(rand() % 4);
        validDirection = true;

        if (m_MoveDirection == EDirection_LEFT)
        {
            if (m_HeadPosition.x <= boundaryValue || currentDir == EDirection_RIGHT)
                validDirection = false;
        }
        else if (m_MoveDirection == EDirection_RIGHT)
        {
            if (m_HeadPosition.x >= (m_Map->cols() - boundaryValue) || currentDir == EDirection_LEFT)
                validDirection = false;
        }
        else if (m_MoveDirection == EDirection_UP)
        {
            if (m_HeadPosition.y >= (m_Map->rows() - boundaryValue) || currentDir == EDirection_DOWN)
                validDirection = false;
        }
        else if (m_MoveDirection == EDirection_DOWN)
        {
            if (m_HeadPosition.y <= boundaryValue || currentDir == EDirection_UP)
                validDirection = false;
        }

    } while (m_MoveDirection == currentDir && !validDirection);

    switch (m_MoveDirection)
    {
    case EDirection_LEFT:
        ChangeCellsPositions(-m_CellSpriteSize, 0);
        break;
    case EDirection_RIGHT:
        ChangeCellsPositions(m_CellSpriteSize, 0);
        break;
    case EDirection_UP:
        ChangeCellsPositions(0, m_CellSpriteSize);
        break;
    case EDirection_DOWN:
        ChangeCellsPositions(0, -m_CellSpriteSize);
        break;
    }

    ChangeCellsSpritePositions();
}

void SnakeComponent::ChangeCellsPositions(int x, int y)
{
    sCellPosition prevCell = m_HeadPosition;
    m_HeadPosition = { m_HeadPosition.x + x, m_HeadPosition.y + y };

    if (!m_TailCellsPositions.empty())
    {
        sCellPosition currentCell;
        for (int i = 0; i < m_TailCellsPositions.size(); i++)
        {
            currentCell = m_TailCellsPositions[i];
            m_TailCellsPositions[i] = prevCell;
            prevCell = currentCell;
        }
    }
}

void SnakeComponent::ChangeCellsSpritePositions()
{
    m_HeadSprite->setPosition(m_HeadPosition.x, m_HeadPosition.y);

    if (m_SnakeCellsCount > 1)
    {
        for (int i = 0; i < m_TailSprites.size(); i++)
        {
            m_TailSprites[i]->setPosition(m_TailCellsPositions[i].x, m_TailCellsPositions[i].y);
        }
    }
}

void SnakeComponent::SetHeadSprite(SpritePtr sprite)
{
    m_HeadSprite = sprite;
    m_HeadSprite->setPosition(m_HeadPosition.x, m_HeadPosition.y);
    m_SnakeCellsCount++;
    this->addChild(m_HeadSprite, 10);
}

SpritePtr SnakeComponent::GetHeadSprite()
{
    return m_HeadSprite;
}

void SnakeComponent::AddCell(float dt)
{
    if (m_SnakeCellsCount < m_MaxSnakeCellsCount)
    {
        m_SnakeCellsCount++;
        SpritePtr newCell =cocos2d::Sprite::createWithSpriteFrame(m_HeadSprite->getSpriteFrame());
        newCell->setScale(0.5);

        auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(32.0f, 32.0f), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
        physicsBody->setDynamic(false);

        newCell->addComponent(physicsBody);

        m_TailSprites.push_back(newCell);

        sCellPosition lastCellPos;
        sCellPosition newCellPos;

        if (!m_TailCellsPositions.empty())
        {
            lastCellPos = m_TailCellsPositions.back();
        }
        else
        {
            lastCellPos = m_HeadPosition;
        }

        switch (m_MoveDirection)
        {
        case EDirection_LEFT:
            newCellPos = { lastCellPos.x + m_CellSpriteSize, lastCellPos.y };
            break;
        case EDirection_RIGHT:
            newCellPos = { lastCellPos.x - m_CellSpriteSize, lastCellPos.y };
            break;
        case EDirection_UP:
            newCellPos = { lastCellPos.x, lastCellPos.y - m_CellSpriteSize };
            break;
        case EDirection_DOWN:
            newCellPos = { lastCellPos.x, lastCellPos.y + m_CellSpriteSize };
            break;
        }

        m_TailCellsPositions.push_back(newCellPos);
        m_TailSprites.back()->setPosition(newCellPos.x, newCellPos.y);

        this->addChild(newCell, 10);
    }
}

void SnakeComponent::VUpdate()
{
    cocos2d::Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SnakeComponent::SnakeMoving), this, 1.0f / m_SnakeSpeed, false);
    cocos2d::Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SnakeComponent::AddCell), this, 3.0f, false);
}

ComponentId SnakeComponent::VGetComponentId(void) const
{
    return m_SnakeId;
}
