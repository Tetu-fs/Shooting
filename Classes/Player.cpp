//Player.h��ǂ�
#include "Player.h"
#include "SimpleAudioEngine.h"

//���O���cocos2d�����悤����Ƃ����錾
USING_NS_CC;

//�萔FRAME_COUNT��錾�A������
const int FRAME_COUNT = 2;

//Player�N���X�̃R���X�g���N�^
//��s�ڂŃw�b�_�[�Ő錾�����ϐ�indexCheck��������
Player::Player()
	: indexCheck(-1)

{

}
Player::~Player()
{
}

//void�^��Player::update(float dt)�֐���錾
//���t���[���X�V���������������ށH
void Player::update(float dt)
{
}

//bool�^��Player::init()�֐���錾
bool Player::init()
{
	int bulletCount = 0;
	//����kawaz_shoothing.png��������Ȃ�������
	if (!Sprite::initWithFile("kawaz_shooting.png"))
	{
		//�Ԃ�l��false��Ԃ�
		return false;
	}

	//�Ԃ�l��true��Ԃ�
	return true;
}

Bullet * Player::shoot()
{
	//Bullet�N���X�̃|�C���^�ϐ�bullet�𐶐�
	Bullet *bullet = Bullet::create();
	//bullet�̈ʒu��Player�̌��ݒn�ɐݒ�
	bullet->setPosition(this->getPosition());
	//bullet�Ɏ擾�����e�N�X�`����^����
	bullet->getTexture()->setAliasTexParameters();
	//���ʉ����Ȃ炷
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shot_se.wav");
	//�߂�l��bullet��Ԃ�
	return bullet;
}


// 0~2�̃A�j���[�V�������Đ����郁�\�b�h(0�ʏ�A1��A2��)
//void�^��Player::playAnimation(int index)�֐����쐬
void Player::playAnimation(int index) {
	//�������ϐ�indexCheck�ƕϐ�index��������������
	if (indexCheck == index) {
		//�����Ŋ֐��̏������I������
		return;
	}

	// �A�j���[�V�����p�̃^�O���Œ�l�Œ�`
	const int ACTION_TAG = 10000; // �D���Ȑ�

	// ���ɃA�j���[�V�����������Ă�����~�߂�
	// �A�j���[�V�����ɂ͑S��10000�̃^�O���t���Ă�͂��Ȃ̂ŁA�d�����Ȃ��悤�Ɏ~�߂�
	this->stopActionByTag(ACTION_TAG);

	// cocos2d::Size�^��frameSize�ϐ��ŕ\�����邩�킸����̃X�v���C�g�̃T�C�Y���w��H
	//Size(frameSize.width, frameSize.height)�ɂ��ꂼ��16.0�������Ă���B�^��float
	auto frameSize = Size(16.0, 16.0);

	//�H
	//�X�v���C�g��X���W0�AY���W0(����)����A16x16��؂�o���H
	//Rect��x,y,width,height��4���Ƃ��B��`�Ƃ����Ӗ�
	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));

	//SpriteFrame*�Ƃ����e���v���[�g��frames�Ƃ����z���錾
	Vector<SpriteFrame*> frames;

	//�ϐ�i��錾�A0�ŏ�������i��FRAME_COUNT�����ł��鎞�A�ϐ�i��1�����Z��{}���̏������s�����[�v
	//i��FRAME_COUNT�����łȂ��Ȃ������Ƀ��[�v�𔲂���
	for (int i = 0; i < FRAME_COUNT; ++i)
	{
		// index�̒l�ɂ����y���W��ς���
		//cocos2d::SpriteFrame�^�̃|�C���g�ϐ�frame��錾
		//�摜kawaz_shooting.png��ǂ݁AframeSize.width��i������2�R�}�A�j���[�V�����̃��[�v
		//index��16(frameSize.height�̒l)�������A�A�j���[�V������؂�ւ�
		//frameSize.width��frameSize.height�ŕ\������摜�̑傫�����w��H
		auto frame = SpriteFrame::create("kawaz_shooting.png", Rect(frameSize.width * i, index * 16, frameSize.width, frameSize.height));

		//�z��frames�̏I����frame�̒l��}������
		frames.pushBack(frame);
	}

	//cocos2d::Animation�^�̃|�C���^�ϐ�animation��錾
	//�z��frames�������Ă���ۂ�����With�Ȃ񂿂�炪�悭�킩��Ȃ�
	auto animation = Animation::createWithSpriteFrames(frames);

	//�|�C���^�ϐ�animation�̕\���Ԋu��0.05�b�ɂ���
	animation->setDelayPerUnit(0.05);

	//cocos2d::RepeatForever�^�̃|�C���^�ϐ�animate��錾�@�Ȃ񂩈ł��ۂ�
	//Animate::create(animation)��animation�Ő錾���ꂽ2�R�}�A�j���𐶐����Ă�Ƃ�����
	//RepeatForever�͐��������A�j���[�V�������𖳌��ɌJ��Ԃ�
	auto animate = RepeatForever::create(Animate::create(animation));

	//�|�C���^�ϐ�animate��ACTION_TAG�Ƃ����^�O��ݒ�
	animate->setTag(ACTION_TAG);

	//animate�Ƃ����A�N�V�����𑖂点��
	this->runAction(animate);

	//indexCheck��index�̒l��������
	indexCheck = index;
}


