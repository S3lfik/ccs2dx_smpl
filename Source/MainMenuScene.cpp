#include "MainMenuScene.h"
#include "GameScene.h"
#include <iostream>

MainMenuLayer::~MainMenuLayer()
{
}

CCScene* MainMenuLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MainMenuLayer *layer = MainMenuLayer::create();

	// Add layer as a child to scene
	scene->addChild(layer);

	// Return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuLayer::init()
{
	if (!CCLayer::init())
		return false;

	// Create main loop
	this->schedule(schedule_selector(MainMenuLayer::update));
	this->setTouchEnabled(true);
	this->setAccelerometerEnabled(true);
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* sprite = CCSprite::create("./textures/Bg.png");
	sprite->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, -1);

	CCMenuItemImage* menuItem = CCMenuItemImage::create("./textures/UI_play.png", "./textures/UI_play.png", this, menu_selector(MainMenuLayer::goToGameScene));
	menuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	CCMenu* menu = CCMenu::create(menuItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	return true;
}

void MainMenuLayer::draw()
{
}

void MainMenuLayer::update(float dt)
{
}

void MainMenuLayer::goToGameScene(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f, GameScene::scene()));
}