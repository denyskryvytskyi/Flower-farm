#ifndef __SNAKE_COMPONENT_H__
#define __SNAKE_COMPONENT_H__

#include "cocos2d.h"
#include "ActorComponent.h"
#include "ResolutionManager.h"
#include "SpriteComponent.h"
#include "Matrix.h"

enum EDirection {
    EDirection_LEFT,
    EDirection_RIGHT,
    EDirection_UP,
    EDirection_DOWN
};

class sCellPosition {
public:
    int x;
    int y;
};

typedef cocos2d::Sprite* SpritePtr;

class SnakeComponent : public ActorComponent
{
private:
    ComponentId m_SnakeId;
    //
    SpritePtr m_HeadSprite;
    std::vector<SpritePtr> m_TailSprites;
    int m_CellSpriteSize = 32;
    //
    sCellPosition m_HeadPosition;
    std::vector<sCellPosition> m_TailCellsPositions;
    short m_SnakeCellsCount;
    const short m_MaxSnakeCellsCount = 5;
    int m_SnakeSpeed;
    EDirection m_MoveDirection;
    //
    Matrix<sCellPosition>* m_Map;

public:
    SnakeComponent(int heightMap, int widthMap, int cellSize, int snakeSpeed);
    ~SnakeComponent();
    //
    void VUpdate() override;
    ComponentId VGetComponentId(void) const override;
    //
    void AddCell(float dt);
    void SetHeadSprite(SpritePtr sprite);
    SpritePtr GetHeadSprite();
    //
    void Setup();
    void SnakeMoving(float dt);
    void ChangeCellsPositions(int x, int y);
    void ChangeCellsSpritePositions();
};

#endif // !__SNAKE_COMPONENT_H__

