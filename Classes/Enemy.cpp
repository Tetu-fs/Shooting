#include "Enemy.h"

//���O���cocos2d�����悤����Ƃ����錾
USING_NS_CC;

const int EFRAME_COUNT = 2;

void Enemy::update(float dt)
{

}

bool Enemy::init(){
	//����bullet.png�݂���Ȃ�������
	if (!Sprite::initWithFile("enemy.png"))
	{
		//�Ԃ�l��false��Ԃ�
		return false;
	}
	// cocos2d::Size�^��EframeSize�ϐ��ŕ\������e�̃X�v���C�g�̃T�C�Y���w��H
	//�ڍׂ͏㕔frameSize�ɂ�
	auto EframeSize = Size(32.0, 32.0);

	//playAnimation(int index)�ƃA�j���[�V�����̐؂�ւ����Ȃ��ȊO�͓���
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
	//���t���[���X�V
	this->scheduleUpdate();
	//�Ԃ�l��true��Ԃ�
	return true;
}