#ifndef __GAMEOVERLAYER_H__
#define __GAMEOVERLAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class HUDLayer : public cocos2d::CCLayer
{
public:
	HUDLayer();
	~HUDLayer();

	// Init method
	virtual bool init();

	// Draw method
	virtual void draw();

	// Main update loop
	void update(float dt);

	// Create instance of scene
	static CCScene* scene();

	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(HUDLayer);

	void updateScore(int score = 1);

	void pauseGame(CCObject* sender);
	void resumeGame(CCObject* sender);

private:
	CCSize m_visibleSize;
	CCPoint m_origin;

	CCLabelBMFont* m_scoreLabel;
	CCLabelBMFont* m_healthLabel;

	CCMenu* m_pauseMenu;
	CCMenu* m_resumeMenu;
	

	int m_score;
};

#endif //__GAMEOVERLAYER_H__