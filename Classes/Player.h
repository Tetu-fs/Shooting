// cocos2d.h��ǂ�
#include "cocos2d.h"

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

	//�N���X�O�ł��Q�Ƃł���
public:

	// void�^��update(float dt)�Ƃ����֐��̐錾�@override�͂��܂��Ȃ��B
	void update(float dt)override;
	// void�^��playAnimation(int index)�Ƃ����֐��̐錾�@override�͂��܂��Ȃ��B
	//������int�^��index�Ƃ����ϐ����錾����Ă���
	void playAnimation(int index);

	//void�^��shot�Ƃ����֐������
	void Shot();

	// cocos2d::Sprite���i�[�ł���|�C���^�z��i�H�j�A_bullets���`����
	cocos2d::Vector<cocos2d::Sprite*> _bullets;

	//cocos2d::Vec2�Ƃ����^��_velocity�Ƃ��������o�ϐ����`���Ă���
	//���̕ϐ��̓L�����N�^�[�̑��x��\���A���t���[�����̑��x�����ݍ��W�ɉ����邱�Ƃňړ����Ă���
	cocos2d::Vec2 _velocity; // �ړ���
	//_Bvelocity�͒e�̑��x��\��
	cocos2d::Vec2 _Bvelocity; // �e�̈ړ���


	//auto Player = Player::create(); �Ɠ����Ӗ��Bbool init();���K�v
	//��L��Player�^��*Player�Ƃ����|�C���^�ϐ���Player::create()�������Ă���
	CREATE_FUNC(Player);
	//Player�N���X�̃R���X�g���N�^�̐錾
	Player();
};
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


	//auto Bullet = Bullet::create(); �Ɠ����Ӗ��Bbool init();���K�v
	//��L��Bullet�^��*Bullet�Ƃ����|�C���^�ϐ���Bullet::create()�������Ă���
	CREATE_FUNC(Bullet);
};