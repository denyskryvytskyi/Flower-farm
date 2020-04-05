#ifndef __SNAKE_GENERATOR_H__
#define __SNAKE_GENERATOR_H__

#include "cocos2d.h"

class SnakeGenerator : public cocos2d::Node
{
private:
    float m_TimeSnakeGeneration = 5.0f;

public:
    void GenerateSnake(float dt);
    void VUpdate();
};

#endif // !__SNAKE_GENERATOR_H__
