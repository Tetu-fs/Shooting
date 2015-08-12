#include "bullet.h"
//���O���cocos2d�����悤����Ƃ����錾
USING_NS_CC;

//�萔FRAME_COUNT��錾�A������
const int BFRAME_COUNT = 2;

//void�^��Bullet::update(float dt)�֐���錾
//���t���[���X�V���������������ށH
void Bullet::update(float dt)
{
	_Bvelocity.normalize();
	const int BSPEED = 15;
	this->setPosition(this->getPosition() + _Bvelocity * BSPEED);

}
//bool�^��Bullet::init()�֐���錾
bool Bullet::init(){
	//����bullet.png�݂���Ȃ�������
	if (!Sprite::initWithFile("bullet.png"))
	{
		//�Ԃ�l��false��Ԃ�
		return false;
	}
	// cocos2d::Size�^��BframeSize�ϐ��ŕ\������e�̃X�v���C�g�̃T�C�Y���w��H
	//�ڍׂ͏㕔frameSize�ɂ�
	auto BframeSize = Size(16.0, 16.0);

	//playAnimation(int index)�ƃA�j���[�V�����̐؂�ւ����Ȃ��ȊO�͓���
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

	//�e��X�����̑��x��1�ɂ���
	_Bvelocity.x = 1;

	//���t���[���X�V
	this->scheduleUpdate();
	//�Ԃ�l��true��Ԃ�
	return true;
}
