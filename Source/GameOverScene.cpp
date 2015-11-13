/*
* (C) 2001-2012 Marmalade. All Rights Reserved.
*
* This document is protected by copyright, and contains information
* proprietary to Marmalade.
*
* This file consists of source code released by Marmalade under
* the terms of the accompanying End User License Agreement (EULA).
* Please do not use this program/source code before you have read the
* EULA and have agreed to be bound by its terms.
*/
#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include <iostream>

GameOverScene::~GameOverScene()
{
}

CCScene* GameOverScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameOverScene *layer = GameOverScene::create();

	// Add layer as a child to scene
	scene->addChild(layer);

	// Return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	if (!CCLayer::init())
		return false;

	// Create main loop
	this->schedule(schedule_selector(GameOverScene::update));
	this->setTouchEnabled(true);

	// COCOS2D TIP
	// Create Cocos2D objects here
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();

	m_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("hightScore");

	CCSprite* sprite = CCSprite::create("./textures/Bg.png");
	sprite->setPosition(CCPoint(m_visibleSize.width * 0.5f, m_visibleSize.height * 0.5f));
	this->addChild(sprite, -1);

	m_gameOverLabel = CCLabelBMFont::create("Game Over", "./fonts/PixelFont.fnt");
	m_gameOverLabel->setPosition(m_visibleSize.width * 0.5f, m_visibleSize.height* 0.8f);
	m_gameOverLabel->setScale(1.5f);
	this->addChild(m_gameOverLabel, 5);

	int score = CCUserDefault::sharedUserDefault()->getIntegerForKey("highScore");
	char chscore[1000];
	sprintf(chscore, "Score: %d", score);
	m_scoreLabel = CCLabelBMFont::create(chscore, "./fonts/PixelFont.fnt");	
	m_scoreLabel->setPosition(m_visibleSize.width * 0.5f, m_visibleSize.height* 0.6f);
	this->addChild(m_scoreLabel, 5);

	CCMenuItemImage* menuItemRetry = CCMenuItemImage::create("./textures/UI_retry.png", "./textures/UI_retry.png", this, menu_selector(GameOverScene::goToGameScene));
	menuItemRetry->setPosition(m_visibleSize.width * 0.3f, m_visibleSize.height * 0.3f);

	CCMenuItemImage* menuItemMenu = CCMenuItemImage::create("./textures/UI_mainmenu.png", "./textures/UI_mainmenu.png", this, menu_selector(GameOverScene::goToMenuScene));
	menuItemMenu->setPosition(m_visibleSize.width * 0.7f, m_visibleSize.height * 0.3f);

	CCMenu* menu = CCMenu::create(menuItemRetry, menuItemMenu, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	return true;
}

void GameOverScene::draw()
{
}

void GameOverScene::update(float dt)
{
}

void GameOverScene::goToGameScene(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f, GameScene::scene()));
}

void GameOverScene::goToMenuScene(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f, MainMenuLayer::scene()));
}