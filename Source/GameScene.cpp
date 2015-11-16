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
#include "GameScene.h"
#include "HUDlayer.h"
#include "BackgroundLayer.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include <memory>

GameScene::~GameScene()
{
}

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // Add layer as a child to scene
    scene->addChild(layer);

    // Return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!CCLayer::init())
        return false;

	this->setTouchEnabled(true);

    // Create main loop
    this->schedule(schedule_selector(GameScene::update));
	//this->schedule(schedule_selector(GameScene::spawnEnemies), 3.f);
	
    // COCOS2D TIP
    // Create Cocos2D objects here
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_origin = CCDirector::sharedDirector()->getVisibleOrigin();

	m_enemies = new CCArray();
	m_removables = new CCArray();
	m_bullets = new CCArray();
	m_removableBullets = new CCArray();

	m_leftRect = CCRectMake(0.f, 0.f, m_visibleSize.width / 2, m_visibleSize.height);
	m_rightRect = CCRectMake(m_visibleSize.width / 2, 0.f, m_visibleSize.width / 2, m_visibleSize.height);

	m_gravity = CCPoint(0.f, -5.f);
	m_jumping = false;
	m_jumpTimer = 0.f;
	m_score = 0;
	m_hp = 100;
	m_timer = 0.f;
	m_paused = false;
	m_actionState = ActionStateNone;
	m_playerState = PlayerStateNone;

	m_background = BackgroundLayer::createBackground(5.f);
	this->addChild((CCLayer*)m_background, -20);
	m_hudLayer = HUDLayer::createHUDLayer();
	this->addChild(m_hudLayer, 10);

	m_hero = CCSprite::create("textures/tinyBazooka.png");
	m_hero->setPosition(CCPoint(m_visibleSize.width / 4, m_visibleSize.height / 2)); 
	this->addChild(m_hero, -5);

	initHeroAnimations();

    return true;
}

void GameScene::initHeroAnimations()
{
	// Animation

	CCSpriteBatchNode * spriteBatch = CCSpriteBatchNode::create("textures/player_anim/player_anim.png");
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("textures/player_anim/player_anim.plist");

	m_hero->createWithSpriteFrameName("player_idle_1.png");
	m_hero->addChild(spriteBatch);

	// Idle Animation

	CCArray* idleAnimFrames = CCArray::createWithCapacity(4);
	char str1[100] = { 0 };
	for (int i = 1; i <= 4; ++i)
	{
		sprintf(str1, "player_idle_%d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str1);
		idleAnimFrames->addObject(frame);
	}
	CCAnimation* idleAnimation = CCAnimation::createWithSpriteFrames(idleAnimFrames, 0.25f);
	m_idleAction = CCRepeatForever::create(CCAnimate::create(idleAnimation));
	m_idleAction->retain();

	// Boost animation

	CCArray* boostAnimaFrames = CCArray::createWithCapacity(4);
	char str2[100] = { 0 };
	for (int i = 1; i <= 4; ++i)
	{
		sprintf(str2, "player_boost_%d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str2);
		boostAnimaFrames->addObject(frame);
	}

	CCAnimation* boostAnimation = CCAnimation::createWithSpriteFrames(boostAnimaFrames, 0.25f);
	m_boostAction = CCRepeatForever::create(CCAnimate::create(boostAnimation));
	m_boostAction->retain();
}

void GameScene::idleAnimation()
{
	
	if (m_actionState == ActionStateIdle)
		return;
	std::cout << "Idle animation" << std::endl;
 	m_hero->stopAllActions();
	m_hero->runAction(m_idleAction);
	m_actionState = ActionStateIdle;
}

void GameScene::boostAnimation()
{
	if (m_actionState == ActionStateBoost)
		return;

	std::cout << "Boost animation" << std::endl;
	m_hero->stopAllActions();
	m_hero->runAction(m_boostAction);
	m_actionState = ActionStateBoost;
}

void GameScene::updateAnimationState()
{
	switch (m_playerState)
	{
	case PlayerStateIdle:
		idleAnimation();
		break;
	case PlayerStateBoost:
		boostAnimation();
		break;

	default: break;
	}
}

void GameScene::update(float dt)
{
	updateHero(dt);
	adaptPlayerPosition();
	updateAnimationState();

	spawnEnemies(dt);	
	updateEnemies(dt);
	updateProjectiles(dt);	

	if (m_hp <= 0)
	{
		gameOver();
	}
	m_background->update();
	// Update Box2D world
	//world->Step(dt, 6, 3);

    // BOX2D TIP
    // Update objects from box2d coordinates here
}

void GameScene::updateHero(float dt)
{
	if (m_jumping)
	{
		m_jumpTimer = 1.f;
		m_jumping = false;
	}

	CCPoint pos = m_hero->getPosition();

	if (m_jumpTimer > 0.f)
	{
		m_playerState = PlayerStateBoost;
		m_jumpTimer -= dt;
		pos.y += 3;
	}
	else
	{
		m_playerState = PlayerStateIdle;
		m_jumpTimer = 0.f;
		pos = ccpAdd(pos, m_gravity);
	}

	m_hero->setPosition(pos);
}

void GameScene::updateProjectiles(float dt)
{
	if (m_bullets->count() > 0)
	{
		CCObject* ob = NULL;
		CCARRAY_FOREACH(m_bullets, ob)
		{
			Projectile* proj = dynamic_cast<Projectile*>(ob);
			proj->update(dt);

			if (proj->getPositionX() < 0.f - proj->getContentSize().width || proj->getPositionX() > m_visibleSize.width + proj->getContentSize().width)
				m_removableBullets->addObject(proj);
			else if (checkCollisions(m_hero, proj) && proj->getType() == Projectile::Bullet)
			{
				m_removableBullets->addObject(proj);
				updateHealth(10); // dmg value here
			}
			else
			{
				for (uint i = 0; i < m_enemies->count(); ++i)
				{
					if (checkCollisions((CCSprite*)m_enemies->objectAtIndex(i), proj) && proj->getType() == Projectile::Rocket)
					{
						m_removableBullets->addObject(proj);
						m_removables->addObject(m_enemies->objectAtIndex(i));
						updateScore(); //score value here
					}
				}
			}
		}
	}

	if (m_removableBullets->count() > 0)
	{
		CCObject* ob = NULL;
		CCARRAY_FOREACH(m_removableBullets, ob)
		{
			Projectile* proj = dynamic_cast<Projectile*>(ob);
			m_removableBullets->removeObject(proj);
			m_bullets->removeObject(proj);
			this->removeChild(proj, true);
			std::cout << "proj removed" << std::endl;
		}
	}
}

void GameScene::updateEnemies(float dt)
{
	if (m_enemies->count() > 0)
	{
		CCObject* ob = NULL;
		CCARRAY_FOREACH(m_enemies, ob)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(ob);
			enemy->update(dt);

			if (enemy->getPositionX() < 0.f - enemy->getContentSize().width)
				m_removables->addObject(enemy);
			else if (checkCollisions(m_hero, enemy))
			{
				m_removables->addObject(enemy);
				updateHealth(20);
				updateScore();
			}
		}
	}


	if (m_removables->count() > 0)
	{
		CCObject* ob = NULL;
		CCARRAY_FOREACH(m_removables, ob)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(ob);
			m_removables->removeObject(enemy);
			m_enemies->removeObject(enemy);
			this->removeChild(enemy, true);
			std::cout << "Enemy removed" << std::endl;
		}
	}
}

void GameScene::updateScore()
{
	++m_score;
	dynamic_cast<HUDLayer*>(m_hudLayer)->updateScoreLabel(m_score);
}

void GameScene::updateHealth(int dmg)
{
	m_hp -= dmg;
	if (m_hp < 0)
		m_hp = 0;

	dynamic_cast<HUDLayer*>(m_hudLayer)->updateHealthLable(m_hp);	
}

void GameScene::spawnEnemies(float dt)
{
	m_timer += dt;

	if (m_timer >= 3.f)
	{
		Enemy* enemy = Enemy::createEnemy("textures/enemy.png");
		this->addChild(enemy, 5);
		m_enemies->addObject(enemy);

		m_timer = 0.f;
	}
	
}

void GameScene::fireRocket()
{
	CCPoint pos = m_hero->getPosition();

	pos.x += m_hero->getContentSize().width / 2;
	pos.y -= m_hero->getContentSize().height / 20;

	Projectile* rocket = Projectile::createProjectile(pos, Projectile::Rocket);
	this->addChild(rocket, -1);
	m_bullets->addObject(rocket);
}

void GameScene::jump()
{
	std::cout << "Jump!" << std::endl;
}

void GameScene::adaptPlayerPosition()
{
	float maxYpos = m_visibleSize.height - m_hero->getContentSize().height / 2;
	float minYpos = m_hero->getContentSize().height;

	CCPoint newPos = m_hero->getPosition();

	newPos.y = std::max(std::min(newPos.y, maxYpos), minYpos);
	m_hero->setPosition(newPos);
}

bool GameScene::checkCollisions(CCSprite* slhs, CCSprite* srhs) const
{
	CCRect lhs = slhs->boundingBox();
	CCRect rhs = srhs->boundingBox();

	if (lhs.intersectsRect(rhs))
		return true;

	return false;
}

void GameScene::gameOver()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("highScore", m_score);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f, GameOverScene::scene()));
}

void GameScene::pauseGame()
{
	std::cout << "GameScene::pauseGame" << std::endl;
	//this->unscheduleUpdate();
	//this->unschedule(schedule_selector(GameScene::spawnEnemies));
	//this->schedule(schedule_selector(GameScene::spawnEnemies), 3.f);
	//if (m_enemies && m_enemies->count() > 0)
	//{
	//	std::cout << "GameScene::pauseGame::count = " << m_enemies->count() << std::endl;
	//	for (unsigned int i = 0; i < m_enemies->count(); ++i)
	//	{
	//		Enemy* en = (Enemy*)m_enemies->objectAtIndex(i);
	//		en->pauseSchedulerAndActions();
	//	}
	//}
	//m_paused = true;
	std::cout << "GameScene::pauseGame" << std::endl;
}

void GameScene::resumeGame()
{
	std::cout << "GameScene::resumeGame" << std::endl;
	//this->unscheduleUpdate();
	//this->schedule(schedule_selector(GameScene::spawnEnemies), 3.f);
	//if (m_enemies->count() > 0)
	//{
	//	for (uint i = 0; i < m_enemies->count(); ++i)
	//	{
	//		Enemy* en = (Enemy*)m_enemies->objectAtIndex(i);
	//		en->resumeSchedulerAndActions();
	//	}
	//}
	//m_paused = false;
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{}

void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->getLocationInView();

	location = CCDirector::sharedDirector()->convertToGL(location);
	
	if (m_rightRect.containsPoint(location))
		fireRocket();
	else if (m_leftRect.containsPoint(location))
		m_jumping = true;
}

void GameScene::goToMenu(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f, MainMenuLayer::scene()));
}

CCArray* GameScene::getBullets() const
{
	return m_bullets;
}