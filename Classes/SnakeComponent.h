#ifndef __SNAKE_COMPONENT_H__
#define __SNAKE_COMPONENT_H__

#include "cocos2d.h"
#include "ActorComponent.h"
#include "ResolutionManager.h"
#include "SpriteComponent.h"

enum eDirection {
	LEFT = 0, RIGHT, UP, DOWN
};

// Position of one cell at the game map
struct sCellPosition {
	int x;
	int y;
};

// The class is responsible for the logic of the snake: movement, growth, acceleration
class SnakeComponent : public ActorComponent
{
private:
	ComponentId m_SnakeId;

	// Sprite
	cocos2d::Sprite* m_HeadSprite;
	std::vector<cocos2d::Sprite*> m_TailSprites;
	int m_CellSpriteSize = 32;

	// Snake attributes
	sCellPosition m_HeadPosition;
	std::vector<sCellPosition> m_TailCellsPositions; // Bunch of cell's positions for the tail of snake
	short m_SnakeCellsCount; // Count of current cells of snake (including head)
	const short m_MaxSnakeCellsCount = 5;
	int m_SnakeSpeed; // Speed of snake without bonus
	eDirection m_MoveDirection; // Snake moving direction

	/*
	/ Map for snake moving.
	/ Consist of squares with size snake's cell
	*/
	const int m_WidthMap;
	const int m_HeightMap;
	sCellPosition** map;
public:
	SnakeComponent(int heightMap, int widthMap, int cellSize, int snakeSpeed);
	~SnakeComponent();

	
	virtual void VUpdate();
	virtual ComponentId VGetComponentId(void) const { return m_SnakeId; };

	// Set sprites for cells
	void AddCell(float dt);
	void SetHeadSprite(cocos2d::Sprite* sprite);
	cocos2d::Sprite* GetHeadSprite() { return m_HeadSprite; }

	// Moving logic
	void Setup();
	void SnakeMoving(float dt);
	void ChangeCellsPositions(int x, int y);
	void ChangeCellsSpritePositions();
};

#endif // __SNAKE_COMPONENT_H__

