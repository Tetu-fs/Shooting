#include "bullet.h"
//名前空間cocos2dをしようするという宣言
USING_NS_CC;

//定数FRAME_COUNTを宣言、初期化
const int BFRAME_COUNT = 2;

//void型のBullet::update(float dt)関数を宣言
//毎フレーム更新したい物をつっこむ？
void Bullet::update(float dt)
{
	_Bvelocity.normalize();
	const int BSPEED = 15;
	this->setPosition(this->getPosition() + _Bvelocity * BSPEED);

}
//bool型のBullet::init()関数を宣言
bool Bullet::init(){
	//もしbullet.pngみつからなかったら
	if (!Sprite::initWithFile("bullet.png"))
	{
		//返り値にfalseを返す
		return false;
	}
	// cocos2d::Size型のBframeSize変数で表示する弾のスプライトのサイズを指定？
	//詳細は上部frameSizeにて
	auto BframeSize = Size(16.0, 16.0);

	//playAnimation(int index)とアニメーションの切り替えがない以外は同じ
	this->setTextureRect(Rect(0, 0, BframeSize.width, BframeSize.height));
	Vector<SpriteFrame*> Bframes;
	for (int j = 0; j < BFRAME_COUNT; ++j)
	{
		auto Bframe = SpriteFrame::create("bullet.png", Rect(BframeSize.width * j, 0, BframeSize.width, BframeSize.height));
		Bframes.pushBack(Bframe);
	}

	auto Banimation = Animation::createWithSpriteFrames(Bframes);
	Banimation->setDelayPerUnit(0.05);
	auto Banimate = RepeatForever::create(Animate::create(Banimation));
	this->runAction(Banimate);

	//弾のX方向の速度を1にする
	_Bvelocity.x = 1;

	//毎フレーム更新
	this->scheduleUpdate();
	//返り値にtrueを返す
	return true;
}
