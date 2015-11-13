#include "Enemy.h"
#include "GameScene.h"

using namespace cocos2d;

Enemy::Enemy()
{}

Enemy::~Enemy()
{}

Enemy* Enemy::createEnemy(std::string filename)
{
	Enemy* ob = new Enemy();
	if (ob && ob->initEnemy(filename))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return nullptr;
}

bool Enemy::initEnemy(std::string filename)
{
	CCSize vizibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//this->schedule(schedule_selector(Enemy::shoot), 2.f);
	m_timer = 0.f;
	m_shootingInterval = 2.f;
	
	int lines = 10; // number of lines for enemies spawning
	int yPosFactor = rand() % lines; // coz we don't want 0 and 1 to be our factors
	float yPosition = (vizibleSize.height / lines) * (yPosFactor > 0 ? yPosFactor : 1);
	
	this->initWithFile(filename.c_str());
	this->setPosition(ccp(vizibleSize.width + this->getContentSize().width / 2, yPosition));

	return true;
}

void Enemy::update(float dt)
{
	m_timer += dt;

	CCPoint pos = this->getPosition();
	CCPoint newPos = CCPoint(pos.x - 50.f * dt, pos.y); // speed to be declared 
	this->setPosition(newPos);	

	shoot(dt);
}

void Enemy::shoot(float dt)
{
	if (m_timer < m_shootingInterval)
		return;

	CCPoint pos = this->getPosition();

	pos.x -= this->getContentSize().width / 2;
	pos.y -= this->getContentSize().height / 20;
	
	Projectile* proj = Projectile::createProjectile(pos, Projectile::Bullet);

	GameScene* layer = (GameScene*)this->getParent();
	layer->addChild(proj, -1);
	layer->getBullets()->addObject(proj);	
	m_timer = 0.f;
}

void Enemy::setShootingInterval(float interval)
{
	m_shootingInterval = interval;
}

float Enemy::getShootingInterval() const
{
	return m_shootingInterval;
}
