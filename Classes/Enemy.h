// cocos2d.h��ǂ�
#include "cocos2d.h"

//Sprite���p������Bullet�N���X�����
class Enemy : public cocos2d::Sprite
{
	//Bullet�̒��ł̂�
protected:

	//CREATE_FUNC���g�p����̂ɕK�v
	//bool�^��init�֐���錾�@override�͂��܂��Ȃ��B
	bool init() override;

	//�N���X�O�ł��Q�Ƃł���
public:
	// void�^��update(float dt)�Ƃ����֐��̐錾�@override�͂��܂��Ȃ��B
	void update(float dt)override;

	//auto Enemy = Enemy::create(); �Ɠ����Ӗ��Bbool init();���K�v
	//��L��Enemy�^��*Enemy�Ƃ����|�C���^�ϐ���Enemy::create()�������Ă���
	CREATE_FUNC(Enemy);
};