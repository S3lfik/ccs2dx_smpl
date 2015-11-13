#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class GameLayer;

class HUDLayer : public cocos2d::CCLayer
{
public:
	HUDLayer();
	~HUDLayer();

	static HUDLayer* createHUDLayer();
	bool initHUDLayer();

	void updateScoreLabel(int score);
	void updateHealthLable(int hp);

	void pauseGame(CCObject* sender);
	void resumeGame(CCObject* sender);

private:
	CCSize m_visibleSize;
	CCPoint m_origin;

	CCLabelBMFont* m_scoreLabel;
	CCLabelBMFont* m_healthLabel;

	CCMenu* m_pauseMenu;
	CCMenu* m_resumeMenu;
	
	GameLayer* m_parent;
};

#endif //__HUDLAYER_H__