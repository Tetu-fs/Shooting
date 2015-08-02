#include "kawaztan.h"

USING_NS_CC;

const int FRAME_COUNT = 2;
Player::Player()
	:test(-1)
{

}

void Player::update(float dt)
{

	_velocity.normalize();
	const int SPEED = 5;
	this->setPosition(this->getPosition() + _velocity * SPEED);

	_Bvelocity.normalize();
	const int BSPEED = 5;
	this->setPosition(this->getPosition() + _Bvelocity * BSPEED);
}

bool Player::init()
{
	test = -1;
	if (!Sprite::initWithFile("kawaz_shooting.png"))
	{
		return false;
	}

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			_velocity.x = -1;

		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			_velocity.x = 1;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			_velocity.y = 1;
			this->playAnimation(1);

		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			_velocity.y = -1;
			this->playAnimation(2);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
			Shot();
		}
	};

	//���Ԃ�L�[�𗣂������̏����B�㉺���E������������
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event) {

		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			_velocity.x = 0.0f;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			_velocity.y = 0.0f;
			this->playAnimation(0);
		}

	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// �A�j���[�V������������
	this->playAnimation(0);

	this->scheduleUpdate();

	return true;
}


// 0~2�̃A�j���[�V�������Đ����郁�\�b�h(0�ʏ�A1��A2��)
void Player::playAnimation(int index) {
	if (test == index) {
		return;
	}

	// �A�j���[�V�����p�̃^�O���Œ�l�Œ�`
	const int ACTION_TAG = 10000; // �D���Ȑ�

	// ���ɃA�j���[�V�����������Ă�����~�߂�
	// �A�j���[�V�����ɂ͑S��10000�̃^�O���t���Ă�͂��Ȃ̂ŁA�d�����Ȃ��悤�Ɏ~�߂�
	this->stopActionByTag(ACTION_TAG);

	// �n�[�h�R�[�f�B���O���Ă悳����
		auto frameSize = Size(16, 16);

		this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		Vector<SpriteFrame*> frames;
		for (int i = 0; i < FRAME_COUNT; ++i)
		{
			// index�̒l�ɂ����y���W��ς���
			auto frame = SpriteFrame::create("kawaz_shooting.png", Rect(frameSize.width * i, index * 16, frameSize.width, frameSize.height));
			frames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(frames);
		animation->setDelayPerUnit(0.05);
		auto animate = RepeatForever::create(Animate::create(animation));
		animate->setTag(ACTION_TAG);
		this->runAction(animate);
		test = index;
}
void Bullet::update(float dt)
{


}

bool Bullet::init(){

	if (!Sprite::initWithFile("bullet.png"))
	{
		return false;
	}

	std::list<int> _bullets(3,1);	
	if (_bullets.size == 3){
		_bullets.pop_front();
	}


	this->scheduleUpdate();

	return true;
}
void Player::Shot() {

	auto BframeSize = Size(16, 16);

	this->setTextureRect(Rect(0, 0, BframeSize.width, BframeSize.height));
	Vector<SpriteFrame*> Bframes;
	for (int i = 0; i < FRAME_COUNT; ++i)
	{
		auto Bframe = SpriteFrame::create("bullet.png", Rect(BframeSize.width * i, 0, BframeSize.width, BframeSize.height));
		Bframes.pushBack(Bframe);
	}
	auto Banimation = Animation::createWithSpriteFrames(Bframes);
	Banimation->setDelayPerUnit(0.05);
	auto Banimate = RepeatForever::create(Animate::create(Banimation));
	auto remove = RemoveSelf::create(true);
	this->runAction(Banimate);

	_Bvelocity.x = 1;
}