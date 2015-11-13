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
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "Enemy.h"

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include <queue>
#include <vector>

class BackgroundLayer;

using namespace cocos2d;

class GameLayer : public cocos2d::CCLayer
{
protected:
    b2World*		world;		// Instance of physics world
public:
    ~GameLayer();
    
    // Init method
    virtual bool init();

	// Main update loop
	void update(float dt);

    // Create instance of scene
    static CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);

	void spawnEnemies(float dt);
	void fireRocket();
	void jump();
	void adaptPlayerPosition();
	bool checkCollisions(CCSprite* slhs, CCSprite* srhs) const;

	void updateProjectiles(float dt);
	void updateEnemies(float dt);

	void updateScore();
	void updateHealth(int dmg);

	void pauseGame();
	void resumeGame();

	
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
	void goToMenu(CCObject* sender);
	void gameOver();

	CCArray* getEnemies() const;
	CCArray* getBullets() const;
private:
	CCSprite* m_hero;
	CCArray* m_enemies;
	CCArray* m_bullets;
	CCArray* m_removables;
	CCArray* m_removableBullets;

	CCRect m_leftRect;
	CCRect	m_rightRect;
	CCPoint m_gravity;

	bool m_jumping;
	float m_jumpTimer;

	CCSize m_visibleSize;
	CCPoint m_origin;

	int m_score;
	int m_hp;

	CCLayer* m_hudLayer;
	BackgroundLayer* m_background;

	CCLabelBMFont* m_scoreLabel;
	CCLabelBMFont* m_healthLabel;

	bool m_paused;
};

#endif // __GAMELAYER_H__

