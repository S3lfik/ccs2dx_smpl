#pragma once
#include "cocos2d.h"

class ScrollingBg;

class BackgroundLayer : cocos2d::CCLayer
{
public:
	BackgroundLayer();
	~BackgroundLayer();

	static BackgroundLayer* createBackground(float speed);

	bool initBackground(float speed);

	void update();

private:
	cocos2d::CCSize m_visibleSize;

	cocos2d::CCSprite* m_background;
	ScrollingBg* m_hills;
	ScrollingBg* m_trees;
	ScrollingBg* m_grass;
	ScrollingBg* m_ground;


	float m_scrollingSpeed;
	
};

