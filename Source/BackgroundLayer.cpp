#include "BackgroundLayer.h"
#include "ScrollingBg.h"

using namespace cocos2d;

BackgroundLayer::BackgroundLayer()
{
}


BackgroundLayer::~BackgroundLayer()
{
}

BackgroundLayer* BackgroundLayer::createBackground(float speed)
{
	BackgroundLayer* ob = new BackgroundLayer();
	if (ob && ob->initBackground(speed))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
	
}

bool BackgroundLayer::initBackground(float speed)
{
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_scrollingSpeed = speed;

	m_background = CCSprite::create("./textures/Bg.png");
	m_background->setPosition(CCPoint(m_visibleSize.width * 0.5f, m_visibleSize.height * 0.5f));
	this->addChild(m_background, -5);

	m_hills = ScrollingBg::create("./textures/hills.png", m_scrollingSpeed * 0.1, m_visibleSize.height * 0.2);
	this->addChild(m_hills, -4);
	m_trees = ScrollingBg::create("./textures/trees.png", m_scrollingSpeed * 0.5, m_visibleSize.height * 0.2);
	this->addChild(m_trees, -3);
	m_ground = ScrollingBg::create("./textures/ground.png", m_scrollingSpeed, 0.f);
	this->addChild(m_ground, -2);
	m_grass = ScrollingBg::create("./textures/grass.png", m_scrollingSpeed, 0.f);
	this->addChild(m_grass, -1);
	

	
	return true;
}

void BackgroundLayer::update()
{
	//std::cout << "BackgroundLayer::update()" << std::endl;
	//int i = 0;
	//while (++i < 1000000){}
	m_hills->update();
	m_trees->update();
	m_grass->update();
	m_ground->update();
}