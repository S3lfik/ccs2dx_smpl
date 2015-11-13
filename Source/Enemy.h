#pragma once

#include "cocos2d.h"
#include "Projectile.h"

class Enemy : public cocos2d::CCSprite
{
public:
	Enemy();
	~Enemy();

	static Enemy* createEnemy(std::string filename);

	bool initEnemy(std::string filename);
	void update(float dt);
	void shoot(float dt);

};