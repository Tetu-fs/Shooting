#include "Enemy.h"

//名前空間cocos2dをしようするという宣言
USING_NS_CC;

const int EFRAME_COUNT = 2;



void Enemy::update(float dt)
{

}

bool ZakoEnemy::init()
{
	if (!Sprite::initWithFile("graphic/enemy.png"))
	{
		//返り値にfalseを返す
		return false;
	}
	// cocos2d::Size型のZakoframeSize変数で表示する弾のスプライトのサイズを指定？
	//詳細は上部frameSizeにて
	auto ZakoframeSize = Size(32.0, 32.0);

	//playAnimation(int index)とアニメーションの切り替えがない以外は同じ
	this->setTextureRect(Rect(0, 0, ZakoframeSize.width, ZakoframeSize.height));
	Vector<SpriteFrame*> Zakoframes;
	for (int j = 0; j < EFRAME_COUNT; ++j)
	{
		auto Zakoframe = SpriteFrame::create("graphic/enemy.png", Rect(ZakoframeSize.width * j, 0, ZakoframeSize.width, ZakoframeSize.height));
		Zakoframes.pushBack(Zakoframe);
	}

	auto Zakoanimation = Animation::createWithSpriteFrames(Zakoframes);
	Zakoanimation->setDelayPerUnit(0.1);
	auto Zakoanimate = RepeatForever::create(Animate::create(Zakoanimation));
	this->runAction(Zakoanimate);
	auto enemyMove = MoveTo::create(4, Vec2(-640, 0));
	this->runAction(enemyMove);

	return true;
}

bool RareEnemy::init()
{
	if ( !Sprite::initWithFile("graphic/boss.png"))
	{
		//返り値にfalseを返す
		return false;
	}
	auto RareframeSize = Size(32.0, 32.0);

	//playAnimation(int index)とアニメーションの切り替えがない以外は同じ
	this->setTextureRect(Rect(0, 0, RareframeSize.width, RareframeSize.height));
	Vector<SpriteFrame*> Rareframes;
	for (int bj = 0; bj < EFRAME_COUNT; ++bj)
	{
		auto Rareframe = SpriteFrame::create("graphic/boss.png", Rect(RareframeSize.width * bj, 0, RareframeSize.width, RareframeSize.height));
		Rareframes.pushBack(Rareframe);
	}

	auto Rareanimation = Animation::createWithSpriteFrames(Rareframes);
	Rareanimation->setDelayPerUnit(0.1);
	auto Rareanimate = RepeatForever::create(Animate::create(Rareanimation));
	this->runAction(Rareanimate);
	auto RareMove = MoveTo::create(2, Vec2(-640, 0));
	this->runAction(RareMove);

	return true;
}

bool Enemy::init(){
	//もしbullet.pngみつからなかったら
	if (!Sprite::initWithFile("graphic/enemy.png"))
	{
		//返り値にfalseを返す
		return false;
	}

	//毎フレーム更新
	this->scheduleUpdate();
	//返り値にtrueを返す
	return true;
}

bool enemyExplosion::init()
{

	if (!Sprite::initWithFile("graphic/explosion_animate.png"))
	{
		//返り値にfalseを返す
		return false;
	}
	const int ExpFRAME_COUNT = 6;
	// cocos2d::Size型のZakoframeSize変数で表示する弾のスプライトのサイズを指定？
	//詳細は上部frameSizeにて
	auto explosionFrameSize = Size(16.0, 16.0);

	//playAnimation(int index)とアニメーションの切り替えがない以外は同じ
	this->setTextureRect(Rect(0, 0, explosionFrameSize.width, explosionFrameSize.height));
	Vector<SpriteFrame*> explosionFrames;
	for (int j = 0; j < ExpFRAME_COUNT; ++j)
	{
		auto explpsionFrame = SpriteFrame::create("graphic/explosion_animate.png", Rect(explosionFrameSize.width * j, 0, explosionFrameSize.width, explosionFrameSize.height));
		explosionFrames.pushBack(explpsionFrame);
	}

	auto explosionAnimation = Animation::createWithSpriteFrames(explosionFrames);
	explosionAnimation->setDelayPerUnit(0.05);
	auto explosionAnimate =Animate::create(explosionAnimation);
	this->runAction(Sequence::create(explosionAnimate, RemoveSelf::create(true), NULL));

	return true;
}
