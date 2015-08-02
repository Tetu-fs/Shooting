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

	//たぶんキーを離した時の処理。上下左右を初期化する
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

	// アニメーションを初期化
	this->playAnimation(0);

	this->scheduleUpdate();

	return true;
}


// 0~2のアニメーションを再生するメソッド(0通常、1上、2下)
void Player::playAnimation(int index) {
	if (test == index) {
		return;
	}

	// アニメーション用のタグを固定値で定義
	const int ACTION_TAG = 10000; // 好きな数

	// 既にアニメーションが動いていたら止める
	// アニメーションには全て10000のタグが付いてるはずなので、重複しないように止める
	this->stopActionByTag(ACTION_TAG);

	// ハードコーディングしてよさそう
		auto frameSize = Size(16, 16);

		this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		Vector<SpriteFrame*> frames;
		for (int i = 0; i < FRAME_COUNT; ++i)
		{
			// indexの値によってy座標を変える
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