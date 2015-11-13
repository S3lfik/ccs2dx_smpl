#pragma once

#include "cocos2d.h"

class ScrollingBg : public cocos2d::CCNode
{
public:
	static ScrollingBg* create(std::string name, float speed, float yPos);
	bool init(std::string name, float speed, float yPos);
	
	
	void update();

private:
	cocos2d::CCSize m_visibleSize;
	
	std::string m_name;
	cocos2d::CCSprite* m_gameBg1;
	cocos2d::CCSprite* m_gameBg2;

	

	float m_speed;	
};

