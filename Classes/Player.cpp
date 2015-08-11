//Player.h��ǂ�
#include "Player.h"

//���O���cocos2d�����悤����Ƃ����錾
USING_NS_CC;

//�萔FRAME_COUNT��錾�A������
const int FRAME_COUNT = 2;

//Player�N���X�̃R���X�g���N�^
//��s�ڂŃw�b�_�[�Ő錾�����ϐ�indexCheck��������
Player::Player()
	:indexCheck(-1)
{

}

//void�^��Player::update(float dt)�֐���錾
//���t���[���X�V���������������ށH
void Player::update(float dt)
{
	//Vec2�^��_velocity�Ƃ����ϐ��𐮐��l�ɒ����H
	_velocity.normalize();
	//SPEED�Ƃ����萔
	const int SPEED = 5;
	//���g�̈ʒu���A���ݒn�{�x�N�g����SPEED�̒l�ɂ���
	this->setPosition(this->getPosition() + _velocity * SPEED);


	_Bvelocity.normalize();
	const int BSPEED = 15;
	this->setPosition(this->getPosition() + _Bvelocity * BSPEED);


}

//bool�^��Player::init()�֐���錾
bool Player::init()
{
	_bullets = Vector<Sprite*>();
	int bulletCount = 0;
	//����kawaz_shoothing.png��������Ȃ�������
	if (!Sprite::initWithFile("kawaz_shooting.png"))
	{
		//�Ԃ�l��false��Ԃ�
		return false;
	}
	//cocos2d::EventListenerKeyboard�^�̃|�C���^�ϐ�keyboardListener��錾���AEventListenerKeyboard::create����
	auto keyboardListener = EventListenerKeyboard::create();
	//�L�[�{�[�h�������ꂽ���̏����������֐��H
	//�ڍׂ悭�킩��Ȃ�
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *event) {
		//���������ꂽ�L�[������������
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			//X�����̑��x��-1�ɂ���
			_velocity.x = -1;

		}
		//�����ł͂Ȃ������A�L�[������������
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			//X�����̑��x��1�ɂ���
			_velocity.x = 1;
		}
		//���������ꂽ�L�[������������
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			//Y�����̑��x��1�ɂ���
			_velocity.y = 1;
			//playAnimation(int index)�̕ϐ�index��1����
			//������ւ̃A�j���[�V�������Đ�
			this->playAnimation(1);

		}
		//�����ł͂Ȃ����������ꂽ�L�[������������
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			//Y�����̑��x��-1�ɂ���
			_velocity.y = -1;
			//playAnimation(int index)�̕ϐ�index��2����
			//�������ւ̃A�j���[�V�������Đ�
			this->playAnimation(2);
		}
		//���������ꂽ�L�[���X�y�[�X�L�[��������
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
			//Shot()�֐��𑖂点��
			Shot();
			//cocos2d::Sprite���i�[�ł���|�C���^�z��i�H�j_bullets�ɒe�𐶐�
			_bullets.pushBack(Sprite::create());
			_Bvelocity.x = 1;
		}
	};

	//���Ԃ�L�[�𗣂������̏����@�ڍׂ킩��Ȃ�
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event) {
		//�����������ꂽ�L�[�����A�܂��́���������
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			//X�����̑��x��0�ɖ߂�
			_velocity.x = 0.0f;
		}
		//�����������ꂽ�L�[�����A�܂��́���������
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			//X�����̑��x��0�ɖ߂�
			_velocity.y = 0.0f;
			//playAnimation(int index)�̕ϐ�index��0����
			//�A�j���[�V������ҋ@�A���ړ��̂��֖̂߂�
			this->playAnimation(0);
		}

	};

	//�L�[�{�[�h�̏�������������̂��܂��Ȃ��݂����Ȃ��́B
	//(��������̃R�����g��蔲����)EventListener���Ă̂ɃL�[���������Ƃ��Ƃ��A�b�����Ƃ��݂����ȏ�����R�t���Ă�����
	//�Ō��EventDispatcher���Ă������̂ɁA�������EventListener��o�^���āA�u�悵�Ȃɂ��肢���܂��v���ē`���鏈��
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// ��L�̒ʂ�A�j���[�V������������
	this->playAnimation(0);
	
	//���t���[���X�V����
	this->scheduleUpdate();

	//�Ԃ�l��true��Ԃ�
	return true;
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

//void�^��Bullet::update(float dt)�֐���錾
//���t���[���X�V���������������ށH
void Bullet::update(float dt)
{


}
//bool�^��Bullet::init()�֐���錾
bool Bullet::init(){
	//����bullet.png�݂���Ȃ�������
	if (!Sprite::initWithFile("bullet.png"))
	{
		//�Ԃ�l��false��Ԃ�
		return false;
	}
	//���t���[���X�V
	this->scheduleUpdate();
	//�Ԃ�l��true��Ԃ�
	return true;
}

//void�^��Player::Shot()�֐����쐬
void Player::Shot() {

	// cocos2d::Size�^��BframeSize�ϐ��ŕ\������e�̃X�v���C�g�̃T�C�Y���w��H
	//�ڍׂ͏㕔frameSize�ɂ�
	auto BframeSize = Size(16.0, 16.0);

	//playAnimation(int index)�ƃA�j���[�V�����̐؂�ւ����Ȃ��ȊO�͓���
	this->setTextureRect(Rect(0, 0, BframeSize.width, BframeSize.height));
	Vector<SpriteFrame*> Bframes;
	for (int j = 0; j < FRAME_COUNT; ++j)
	{
		auto Bframe = SpriteFrame::create("bullet.png", Rect(BframeSize.width * j, 0, BframeSize.width, BframeSize.height));
		Bframes.pushBack(Bframe);
	}

	auto Banimation = Animation::createWithSpriteFrames(Bframes);
	Banimation->setDelayPerUnit(0.05);
	auto Banimate = RepeatForever::create(Animate::create(Banimation));
	this->runAction(Banimate);

	//�e��X�����̑��x��1�ɂ���


}