#pragma once

#include "cocos2d.h"

class Projectile : public cocos2d::CCSprite
{
public:
	enum Type
	{
		Rocket,
		Bullet,
		None
	};

public:
	Projectile();
	~Projectile();

	static Projectile* createProjectile(cocos2d::CCPoint point, Type type);
	bool initProjectile(cocos2d::CCPoint point, Type type);
	void update(float dt);

	int getType() const;

private:
	Type m_type;
};

