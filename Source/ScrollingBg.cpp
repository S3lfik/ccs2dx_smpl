#include "ScrollingBg.h"

using namespace cocos2d;

ScrollingBg* ScrollingBg::create(std::string name, float speed, float yPos)
{
	ScrollingBg* ob = new ScrollingBg();
	if (ob && ob->init(name, speed, yPos))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}

bool ScrollingBg::init(std::string name, float speed, float yPos)
{
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_speed = speed;

	m_gameBg1 = CCSprite::create(name.c_str());
	m_gameBg1->setPosition(CCPoint(0.f, yPos));
	m_gameBg1->setAnchorPoint(CCPoint(0.0f, 0.f));
	this->addChild(m_gameBg1);

	m_gameBg2 = CCSprite::create(name.c_str());
	m_gameBg2->setPosition(CCPoint(m_visibleSize.width, yPos));
	m_gameBg2->setAnchorPoint(CCPoint(0.0f, 0.f));
	this->addChild(m_gameBg2);

	return true;
}

void ScrollingBg::update()
{
	CCPoint bg1 = m_gameBg1->getPosition();
	CCPoint bg2 = m_gameBg2->getPosition();

	if (bg1.x < -m_visibleSize.width)
		bg1.x = bg2.x + m_visibleSize.width;
	if (bg2.x < -m_visibleSize.width)
		bg2.x = bg1.x + m_visibleSize.width;

	m_gameBg1->setPosition(ccp(bg1.x - m_speed, bg1.y));
	m_gameBg2->setPosition(ccp(bg2.x - m_speed, bg2.y)); 
}
