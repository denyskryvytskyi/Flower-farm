#ifndef __MOUSE_SCENE_H__
#define __MOUSE_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
private:
	// Not enough coins label
	cocos2d::Label* m_NotEnoughCoins;
	cocos2d::Label* m_StartGameLabel;

	cocos2d::PhysicsWorld* sceneWorld;

	// player has at least 50 coins
	int m_PlayerCoinsCount; 
	bool m_GameIsStarted = false;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float dt);
	CREATE_FUNC(MainScene);
	
private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	void onContactBegin(cocos2d::PhysicsContact &contact);
};

#endif // __MOUSE_SCENE_H__