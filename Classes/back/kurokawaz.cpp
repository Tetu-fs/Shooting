#include "cocos2d.h"
USING_NS_CC;
Vec2 _velocity = Vec2(0, 0); // �ړ���

bool GameplayLayer::init()
{
	//////////////////////////////
	// 1. �ŏ��ɐe�N���X�̏��������s���B
	if (!Layer::init())
	{
		return false;
	}
	// 2. ��l���̃X�v���C�g���쐬����B
	auto kurokawaz = Sprite::create("mapchip_03.png");
	kurokawaz->setScale(2.0f);
	kurokawaz->setPosition(Vec2(64, 64));

	return true;
}
