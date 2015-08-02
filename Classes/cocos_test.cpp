#include "cocos_test.h"

USING_NS_CC;
extern int index;
MainScene::MainScene()
	:_stage(nullptr)
	,_kawaztan(nullptr)
	,_bullet(nullptr)
{


}

MainScene::~MainScene()
{
	CC_SAFE_RELEASE_NULL(_stage);
	CC_SAFE_RELEASE_NULL(_kawaztan);
	CC_SAFE_RELEASE_NULL(_bullet);

}

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	
	return scene;
}

void MainScene::update(float dt) {



}

bool MainScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	auto stage = Stage::create();
	this->addChild(stage);
	this->setStage(stage);

	auto kawaztan = Player::create();
	kawaztan->setPosition(Vec2(64, 240));
	this->addChild(kawaztan);
	this->setPlayer(kawaztan);
	kawaztan->getTexture()->setAliasTexParameters();
	kawaztan->setScale(2.0f);
	this->scheduleUpdate();

	auto bullet = Bullet::create();
	kawaztan->addChild(bullet);
	_bullets.push_back(bullet);

	//初期化処理
	return true;
}