// cocos2d.h��ǂ�
#include "cocos2d.h"
#include "bullet.h"

//Sprite���p������Player�N���X�����
class Player : public cocos2d::Sprite
{
	//Player�̒��ł̂�
protected:
	
	//CREATE_FUNC���g�p����̂ɕK�v
	//bool�^��init�֐���錾�@override�͂��܂��Ȃ��B
	bool init() override;

	//������������int�^��indexCheck�Ƃ����ϐ���錾
	int indexCheck;

	//Player�N���X�̃R���X�g���N�^�̐錾
	Player();
	//virtual�͉��z�֐��Ƃ������܂��Ȃ��@�f�X�g���N�^�̐錾
	virtual ~Player();


	//�N���X�O�ł��Q�Ƃł���
public:
	

	// void�^��update(float dt)�Ƃ����֐��̐錾�@override�͂��܂��Ȃ��B
	void update(float dt)override;

	//void�^��playerShot��錾
	void Player::playerShot();


	// void�^��playAnimation(int index)�Ƃ����֐��̐錾�@override�͂��܂��Ȃ��B
	//������int�^��index�Ƃ����ϐ����錾����Ă���
	void playAnimation(int index);

	CC_SYNTHESIZE_RETAIN(Bullet*, _bullet, Bullet);

	//auto Player = Player::create(); �Ɠ����Ӗ��Bbool init();���K�v
	//��L��Player�^��*Player�Ƃ����|�C���^�ϐ���Player::create()�������Ă���
	CREATE_FUNC(Player);

};
