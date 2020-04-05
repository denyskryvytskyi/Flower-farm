#ifndef __MOUSE_SCENE_H__
#define __MOUSE_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
private:
	cocos2d::PhysicsWorld* sceneWorld;

	int m_PlayerCoinsCount; 
	bool m_GameIsStarted = false;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);
	
private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
};

#endif // !__MOUSE_SCENE_H__