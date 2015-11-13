#ifndef __GAMEOVERLAYER_H__
#define __GAMEOVERLAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class GameOverScene : public cocos2d::CCLayer
{
protected:
	b2World*		world;		// Instance of physics world
public:
	~GameOverScene();

	// Init method
	virtual bool init();

	// Draw method
	virtual void draw();

	// Main update loop
	void update(float dt);

	// Create instance of scene
	static CCScene* scene();

	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(GameOverScene);

	void goToGameScene(CCObject* sender);
	void goToMenuScene(CCObject* sender);

private:
	CCSize m_visibleSize;
	CCPoint m_origin;

	CCLabelBMFont* m_gameOverLabel;
	CCLabelBMFont* m_scoreLabel;

	int m_score;
};

#endif //__GAMEOVERLAYER_H__