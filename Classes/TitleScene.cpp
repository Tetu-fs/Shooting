#include "TitleScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene *TitleScene::createScene()
{

	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);

	return scene;
}

TitleScene::TitleScene()
	: _howto(nullptr)
{

}

TitleScene::~TitleScene()
{

		CC_SAFE_RELEASE_NULL(_howto);
}
void TitleScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("title_jingle.mp3", false);
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	auto logo = Sprite::create("title_logo.png");
	logo->setPosition(Vec2(320, 400));
	logo->getTexture()->setAliasTexParameters();
	logo->setScale(2.0f);
	this->addChild(logo);

	auto HowToMove = Label::createWithSystemFont("Move : ArrowKey or WASD", "arial", 18);
	HowToMove->setPosition(Vec2(320, 260));
	this->addChild(HowToMove);

	auto HowToShot = Label::createWithSystemFont("Shot : Space", "arial", 18);
	HowToShot->setPosition(Vec2(320, 220));
	this->addChild(HowToShot);

	auto ClickStart = Label::createWithSystemFont("Click to Start", "arial", 24);
	ClickStart->setPosition(Vec2(320, 160));
	this->addChild(ClickStart);
	//ゲームスタートボタン処理
	auto start = Sprite::create("start.png");
	start->setPosition(Vec2(320, 80));
	this->addChild(start);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event){
		log("touch");
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("level_se.wav");
		this->getEventDispatcher()->removeAllEventListeners();

		auto delay = DelayTime::create(0.5);

		auto startGame = CallFunc::create([]{
			auto scene = MainScene::createScene();
			auto transition = TransitionFade::create(1.0f, scene);
			Director::getInstance()->replaceScene(transition);
		});
		this->runAction(Sequence::create(delay, startGame, NULL));

		auto start_press = Sprite::create("start_press.png");
		start_press->setPosition(Vec2(320, 80));
		this->addChild(start_press);


		this->scheduleUpdate();
		return true;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

