#include "SnakeComponent.h"

SnakeComponent::SnakeComponent(int heightMap, int widthMap, int cellSize, int snakeSpeed)
	:m_HeightMap(heightMap), m_WidthMap(widthMap), m_CellSpriteSize(cellSize), m_SnakeSpeed(snakeSpeed), m_SnakeCellsCount(0)
{
	map = new sCellPosition*[heightMap];
	for (int i = 0; i < heightMap; i++)
	{
		map[i] = new sCellPosition[widthMap];
	}
}

SnakeComponent::~SnakeComponent()
{}

void SnakeComponent::Setup()
{
	// Set start settings for the snake
	// Set head position
	srand(time(0));
	int x = 100 + rand() % (m_WidthMap - 100);
	int y = 100 + rand() % (m_HeightMap - 100);
	m_HeadPosition = { x, y };

	// Set direction
	m_MoveDirection = static_cast<eDirection>(rand() % 4);
}

void SnakeComponent::SnakeMoving(float dt)
{
	// cocos2d::log("Snake moves");
	// Change direction
	eDirection currentDir = m_MoveDirection;

	// Check out if the snake don't move out of the map or towards its tail
	bool validDirection;
	int boundaryValue = m_CellSpriteSize;

	do {
		// Generate random direction
		m_MoveDirection = static_cast<eDirection>(rand() % 4);
		validDirection = true;

		// Check out generated direction
		
		cocos2d::log("y: %d; h: %d", m_HeadPosition.y, m_HeightMap);
		cocos2d::log("x: %d; w: %d", m_HeadPosition.x, m_WidthMap);
		if (m_MoveDirection == LEFT)
		{
			if(m_HeadPosition.x <= boundaryValue || currentDir == RIGHT)
				validDirection = false;
		}
		else if (m_MoveDirection == RIGHT)
		{
			if (m_HeadPosition.x >= (m_WidthMap - boundaryValue) || currentDir == LEFT)
				validDirection = false;	
		}
		else if (m_MoveDirection == UP)
		{
			if (m_HeadPosition.y >= (m_HeightMap - boundaryValue) || currentDir == DOWN)
				validDirection = false;
		}
		else if (m_MoveDirection == DOWN)
		{
			if(m_HeadPosition.y <= boundaryValue || currentDir == UP)
				validDirection = false;
		}

	} while (m_MoveDirection == currentDir && !validDirection);

	switch (m_MoveDirection)
	{
		case LEFT: ChangeCellsPositions(-m_CellSpriteSize, 0);
			break;
		case RIGHT:  ChangeCellsPositions(m_CellSpriteSize, 0);
			break;
		case UP: ChangeCellsPositions(0, m_CellSpriteSize);
			break;
		case DOWN:  ChangeCellsPositions(0, -m_CellSpriteSize);
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

void SnakeComponent::SetHeadSprite(cocos2d::Sprite* sprite)
{
	m_HeadSprite = sprite;
	m_HeadSprite->setPosition(m_HeadPosition.x, m_HeadPosition.y);
	m_SnakeCellsCount++;
	this->addChild(m_HeadSprite, 10);
}

void SnakeComponent::AddCell(float dt)
{
	//cocos2d::log("Add cell");
	cocos2d::log("Cells: %d", m_SnakeCellsCount);
	if (m_SnakeCellsCount < m_MaxSnakeCellsCount)
	{
		m_SnakeCellsCount++;
		cocos2d::Sprite* newCell = cocos2d::Sprite::createWithSpriteFrame(m_HeadSprite->getSpriteFrame());
		newCell->setScale(0.5);

		// Add physics for new cells
		auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(32.0f, 32.0f), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setDynamic(false);
		// sprite will use physicsBody
		newCell->addComponent(physicsBody);

		m_TailSprites.push_back(newCell);
		
		sCellPosition lastCellPos;
		sCellPosition newCellPos;

		// If tail has cells get position of the last one
		if (!m_TailCellsPositions.empty())
		{
			lastCellPos = m_TailCellsPositions.back();
		}
		// If not - last cell position - snake's head position
		else 
		{
			lastCellPos = m_HeadPosition;
		}

		// According  to direction add new cell to the tail's end
		switch (m_MoveDirection)
		{
		case LEFT: newCellPos = { lastCellPos.x + m_CellSpriteSize, lastCellPos.y };
			break;
		case RIGHT: newCellPos = { lastCellPos.x - m_CellSpriteSize, lastCellPos.y };
			break;
		case UP: newCellPos = { lastCellPos.x, lastCellPos.y - m_CellSpriteSize };
			break;
		case DOWN:  newCellPos = { lastCellPos.x, lastCellPos.y + m_CellSpriteSize };
			break;
		}

		m_TailCellsPositions.push_back(newCellPos);
		m_TailSprites.back()->setPosition(newCellPos.x, newCellPos.y);

		this->addChild(newCell, 10);
	}
}

void SnakeComponent::VUpdate()
{
	// Moving while snake has at least one cell
	cocos2d::Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SnakeComponent::SnakeMoving), this, 1.0f/m_SnakeSpeed, false);
	cocos2d::Director::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SnakeComponent::AddCell), this, 3.0f, false);
}