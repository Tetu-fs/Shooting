// cocos2d.h��ǂ�
#include "cocos2d.h"

//Sprite���p������Bullet�N���X�����
class Bullet : public cocos2d::Sprite
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

	//_Bvelocity�͒e�̑��x��\��
	cocos2d::Vec2 _Bvelocity; // �e�̈ړ���

	//auto Bullet = Bullet::create(); �Ɠ����Ӗ��Bbool init();���K�v
	//��L��Bullet�^��*Bullet�Ƃ����|�C���^�ϐ���Bullet::create()�������Ă���
	CREATE_FUNC(Bullet);
};