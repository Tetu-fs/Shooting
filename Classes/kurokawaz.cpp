#include "cocos2d.h"
USING_NS_CC;
Vec2 _velocity = Vec2(0, 0); // 移動量

bool GameplayLayer::init()
{
	//////////////////////////////
	// 1. 最初に親クラスの初期化を行う。
	if (!Layer::init())
	{
		return false;
	}
	// 2. 主人公のスプライトを作成する。
	auto kurokawaz = Sprite::create("mapchip_03.png");
	kurokawaz->setScale(2.0f);
	kurokawaz->setPosition(Vec2(64, 64));

	return true;
}
