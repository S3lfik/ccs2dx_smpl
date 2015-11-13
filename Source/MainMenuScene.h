#ifndef __MENULAYER_H__
#define __MENULAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class MainMenuLayer : public cocos2d::CCLayer
{
protected:
	b2World*		world;		// Instance of physics world
public:
	~MainMenuLayer();

	// Init method
	virtual bool init();

	// Draw method
	virtual void draw();

	// Main update loop
	void update(float dt);

	// Create instance of scene
	static CCScene* scene();

	CREATE_FUNC(MainMenuLayer);

	void goToGameScene(CCObject* sender);

};

#endif //__MENULAYER_H__