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
#include "HUDlayer.h"
#include "GameLayer.h"
#include "MainMenuScene.h"
#include <iostream>

HUDLayer::HUDLayer()
{
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
}
HUDLayer::~HUDLayer()
{
}

CCScene* HUDLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HUDLayer *layer = HUDLayer::create();

	// Add layer as a child to scene
	scene->addChild(layer);

	// Return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HUDLayer::init()
{
	if (!CCLayer::init())
		return false;

	// Create main loop
	this->schedule(schedule_selector(HUDLayer::update));
	this->setTouchEnabled(true);

	// COCOS2D TIP
	// Create Cocos2D objects here
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();

/// Labels
	m_scoreLabel = CCLabelBMFont::create("S: 0", "./fonts/PixelFont.fnt");
	m_scoreLabel->setPosition(m_visibleSize.width * 0.05f, m_visibleSize.height* 0.9f);
	m_scoreLabel->setScale(0.5f);
	m_scoreLabel->setAnchorPoint(CCPoint(0.f, 0.5f));
	this->addChild(m_scoreLabel, 5);

	m_healthLabel = CCLabelBMFont::create("L: 100", "./fonts/PixelFont.fnt");
	m_healthLabel->setPosition(m_visibleSize.width * 0.1f, m_visibleSize.height* 0.1f);
	m_healthLabel->setScale(0.5f);
	this->addChild(m_healthLabel, 5);
///

/// Menus
	CCMenuItemImage* pauseMenuItem = CCMenuItemImage::create("./textures/UI__pause.png", "./textures/UI__pause.png", this, menu_selector(HUDLayer::pauseGame));
	pauseMenuItem->setPosition(m_visibleSize.width * 0.9f, m_visibleSize.height * 0.9f);

	m_pauseMenu = CCMenu::create(pauseMenuItem, NULL);
	m_pauseMenu->setPosition(CCPointZero);
	this->addChild(m_pauseMenu);

	//
	CCMenuItemImage* resumeMenuItem = CCMenuItemImage::create("./textures/UI__pause.png", "./textures/UI__pause.png", this, menu_selector(HUDLayer::pauseGame));
	resumeMenuItem->setPosition(m_visibleSize.width * 0.9f, m_visibleSize.height * 0.9f);

	m_resumeMenu = CCMenu::create(resumeMenuItem, NULL);
	m_resumeMenu->setPosition(CCPointZero);
	
///

	return true;
}

void HUDLayer::pauseGame(CCObject* sender)
{
	/*
		reffer to game scene to pause the game 
	*/
	std::cout << "Pause" << std::endl;
	this->removeChild(m_pauseMenu, true);
	this->addChild(m_resumeMenu, 5);
}

void HUDLayer::resumeGame(CCObject* sender)
{
	/*
	reffer to game scene to pause the game
	*/
	std::cout << "Resume" << std::endl;
	this->removeChild(m_resumeMenu, true);
	this->addChild(m_pauseMenu, 5);
}

void HUDLayer::draw()
{
}

void HUDLayer::update(float dt)
{
}