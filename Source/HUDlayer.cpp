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
}
HUDLayer::~HUDLayer()
{
	std::cout << "HUDLayer::~HUDLayer()" << std::endl;
	//m_pauseMenu->autorelease();
	//m_resumeMenu->autorelease();

	while (m_pauseMenu->retainCount() > 1)
		m_pauseMenu->release();
	while (m_resumeMenu->retainCount() > 1)
		m_resumeMenu->release();
	std::cout << m_pauseMenu->retainCount() << std::endl;
	std::cout << m_resumeMenu->retainCount() << std::endl;
}

HUDLayer* HUDLayer::createHUDLayer()
{
	HUDLayer* ob = new HUDLayer();
	if (ob && ob->initHUDLayer())
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}

// on "init" you need to initialize your instance
bool HUDLayer::initHUDLayer()
{
	if (!CCLayer::init())
		return false;

	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// Create main loop
	this->setTouchEnabled(true);

	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();

	m_parent = (GameLayer*)this->getParent();

/// Labels
	m_scoreLabel = CCLabelBMFont::create("S: 0", "./fonts/PixelFont.fnt");
	m_scoreLabel->setPosition(m_visibleSize.width * 0.05f, m_visibleSize.height* 0.9f);
	m_scoreLabel->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
	m_scoreLabel->setScale(0.5f);
	m_scoreLabel->setAnchorPoint(CCPoint(0.f, 0.5f));
	this->addChild(m_scoreLabel, 5);
	//
	m_healthLabel = CCLabelBMFont::create("HP: 100", "./fonts/PixelFont.fnt");
	m_healthLabel->setPosition(m_visibleSize.width * 0.05f, m_visibleSize.height* 0.1f);
	m_healthLabel->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
	m_healthLabel->setScale(0.5f);
	m_healthLabel->setAnchorPoint(CCPoint(0.f, 0.5f));
	this->addChild(m_healthLabel, 5);
///

/// Menus
	CCMenuItemImage* pauseMenuItem = CCMenuItemImage::create("./textures/UI_pause.png", "./textures/UI_pause.png", this, menu_selector(HUDLayer::pauseGame));
	pauseMenuItem->setPosition(m_visibleSize.width * 0.9f, m_visibleSize.height * 0.9f);

	m_pauseMenu = CCMenu::create(pauseMenuItem, NULL);
	m_pauseMenu->setPosition(CCPointZero);
	this->addChild(m_pauseMenu);
	m_pauseMenu->retain();
	//
	CCMenuItemImage* resumeMenuItem = CCMenuItemImage::create("./textures/UI_retry.png", "./textures/UI_retry.png", this, menu_selector(HUDLayer::resumeGame));
	resumeMenuItem->setPosition(m_visibleSize.width * 0.9f, m_visibleSize.height * 0.9f);
	m_resumeMenu = CCMenu::create(resumeMenuItem, NULL);
	m_resumeMenu->setPosition(CCPointZero);
	m_resumeMenu->retain();
	
	
///

	return true;
}

void HUDLayer::updateScoreLabel(int score)
{
	char chScore[100];
	sprintf(chScore, "S: %d", score);
	m_scoreLabel->setString(chScore);
}

void HUDLayer::updateHealthLable(int hp)
{
	char health[100];
	sprintf(health, "HP: %d", hp);
	m_healthLabel->setString(health);
}

void HUDLayer::pauseGame(CCObject* sender)
{
	this->removeChild(m_pauseMenu/*, true*/);
	this->addChild(m_resumeMenu, 5);
	m_parent->pauseGame();
}

void HUDLayer::resumeGame(CCObject* sender)
{
	this->removeChild(m_resumeMenu/*, true*/);
	this->addChild(m_pauseMenu, 5);
	m_parent->resumeGame();
}