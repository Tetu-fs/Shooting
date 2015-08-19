#include "Enemy.h"

//名前空間cocos2dをしようするという宣言
USING_NS_CC;

const int EFRAME_COUNT = 2;

void Enemy::update(float dt)
{

}

bool Enemy::init(){
	//もしbullet.pngみつからなかったら
	if (!Sprite::initWithFile("enemy.png"))
	{
		//返り値にfalseを返す
		return false;
	}
	// cocos2d::Size型のEframeSize変数で表示する弾のスプライトのサイズを指定？
	//詳細は上部frameSizeにて
	auto EframeSize = Size(32.0, 32.0);

	//playAnimation(int index)とアニメーションの切り替えがない以外は同じ
	this->setTextureRect(Rect(0, 0, EframeSize.width, EframeSize.height));
	Vector<SpriteFrame*> Eframes;
	for (int j = 0; j < EFRAME_COUNT; ++j)
	{
		auto Eframe = SpriteFrame::create("enemy.png", Rect(EframeSize.width * j, 0, EframeSize.width, EframeSize.height));
		Eframes.pushBack(Eframe);
	}

	auto Banimation = Animation::createWithSpriteFrames(Eframes);
	Banimation->setDelayPerUnit(0.1);
	auto Banimate = RepeatForever::create(Animate::create(Banimation));
	this->runAction(Banimate);
	auto enemyMove = MoveTo::create(6, Vec2(-600,0 ) );
	this->runAction(enemyMove);
	//毎フレーム更新
	this->scheduleUpdate();
	//返り値にtrueを返す
	return true;
}