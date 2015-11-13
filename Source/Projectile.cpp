#include "Projectile.h"
using namespace cocos2d;

Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

Projectile* Projectile::createProjectile(cocos2d::CCPoint point, Type type)
{
	Projectile* projectile = new Projectile();
	if (projectile && projectile->initProjectile(point, type))
	{
		projectile->autorelease();
		return projectile;
	}

	CC_SAFE_DELETE(projectile);
	return NULL;
}

bool Projectile::initProjectile(cocos2d::CCPoint point, Type type)
{
	CCSize vizibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	
	m_type = type;
	bool result = true;

	if (m_type == Rocket)
		result = this->initWithFile("./textures/rocket.png");
	else if (m_type == Bullet)
		result = this->initWithFile("./textures/bullet.png");

	this->setPosition(point);
	return result;
}

void Projectile::update(float dt)
{
	CCPoint pos = this->getPosition();
	CCPoint newPos(0.f, 0.f);

	switch (m_type)
	{
	case Bullet:
		newPos = CCPoint(pos.x - 70.f * dt, pos.y);
		break;
	case Rocket:
		newPos = CCPoint(pos.x + 70.f * dt, pos.y);
		break;
	}
	this->setPosition(newPos);
}

int Projectile::getType() const
{
	return m_type;
}