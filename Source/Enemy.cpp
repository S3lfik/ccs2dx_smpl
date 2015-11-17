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
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//this->schedule(schedule_selector(Enemy::shoot), 2.f);
	m_timer = 0.f;
	m_shootingInterval = 2.f;

	this->initWithFile(filename.c_str());
	float minYPos = this->getContentSize().height;
	float maxYpos = visibleSize.height - this->getContentSize().height;
	float yPos = float(rand() % int(maxYpos - minYPos));
	yPos = MIN(maxYpos, MAX(minYPos, minYPos + yPos));
	this->setPosition(ccp(visibleSize.width + this->getContentSize().width / 2, yPos));

	CCSpriteBatchNode * spriteBatch = CCSpriteBatchNode::create("textures/enemy_anim/enemy_anim.png");
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("textures/enemy_anim/enemy_anim.plist");

	this->createWithSpriteFrameName("enemy_anim_1.png");
	this->addChild(spriteBatch);

	CCArray* enemyAnimFrames = CCArray::createWithCapacity(4);
	char str1[100] = { 0 };
	for (int i = 1; i <= 4; ++i)
	{
		sprintf(str1, "enemy_anim_%d.png", i); 
		CCSpriteFrame* frame = cache->spriteFrameByName(str1);
		enemyAnimFrames->addObject(frame);
	}
	CCAnimation* enemy_anim = CCAnimation::createWithSpriteFrames(enemyAnimFrames, 0.25f);
	CCAction* enemyAnimAction = CCRepeatForever::create(CCAnimate::create(enemy_anim));
	this->runAction(enemyAnimAction);



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
	layer->addChild(proj, -5);
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
